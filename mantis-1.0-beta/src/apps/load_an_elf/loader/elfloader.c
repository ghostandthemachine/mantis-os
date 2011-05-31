/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * @(#)$Id: elfloader-tmp.c,v 1.1 2006/06/17 22:41:18 adamdunkels Exp $
 */

#include "loader/elfloader.h"
#include "loader/elfloader-arch.h"
#include "elfstore/elfstore.h"
#include "loader/symtab.h"

#include <stddef.h>
#include <string.h>

#if 0
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...) do {} while (0)
#endif

#define EI_NIDENT 16

struct elf32_ehdr {
  unsigned char e_ident[EI_NIDENT];    /* ident bytes */
  elf32_half e_type;                   /* file type */
  elf32_half e_machine;                /* target machine */
  elf32_word e_version;                /* file version */
  elf32_addr e_entry;                  /* start address */
  elf32_off e_phoff;                   /* phdr file offset */
  elf32_off e_shoff;                   /* shdr file offset */
  elf32_word e_flags;                  /* file flags */
  elf32_half e_ehsize;                 /* sizeof ehdr */
  elf32_half e_phentsize;              /* sizeof phdr */
  elf32_half e_phnum;                  /* number phdrs */
  elf32_half e_shentsize;              /* sizeof shdr */
  elf32_half e_shnum;                  /* number shdrs */
  elf32_half e_shstrndx;               /* shdr string index */
};

/* Values for e_type. */
#define ET_NONE         0       /* Unknown type. */
#define ET_REL          1       /* Relocatable. */
#define ET_EXEC         2       /* Executable. */
#define ET_DYN          3       /* Shared object. */
#define ET_CORE         4       /* Core file. */

struct elf32_shdr {
  elf32_word sh_name; 		/* section name */
  elf32_word sh_type; 		/* SHT_... */
  elf32_word sh_flags; 	        /* SHF_... */
  elf32_addr sh_addr; 		/* virtual address */
  elf32_off sh_offset; 	        /* file offset */
  elf32_word sh_size; 		/* section size */
  elf32_word sh_link; 		/* misc info */
  elf32_word sh_info; 		/* misc info */
  elf32_word sh_addralign; 	/* memory alignment */
  elf32_word sh_entsize; 	/* entry size if table */
};

/* sh_type */
#define SHT_NULL        0               /* inactive */
#define SHT_PROGBITS    1               /* program defined information */
#define SHT_SYMTAB      2               /* symbol table section */
#define SHT_STRTAB      3               /* string table section */
#define SHT_RELA        4               /* relocation section with addends*/
#define SHT_HASH        5               /* symbol hash table section */
#define SHT_DYNAMIC     6               /* dynamic section */
#define SHT_NOTE        7               /* note section */
#define SHT_NOBITS      8               /* no space section */
#define SHT_REL         9               /* relation section without addends */
#define SHT_SHLIB       10              /* reserved - purpose unknown */
#define SHT_DYNSYM      11              /* dynamic symbol table section */
#define SHT_LOPROC      0x70000000      /* reserved range for processor */
#define SHT_HIPROC      0x7fffffff      /* specific section header types */
#define SHT_LOUSER      0x80000000      /* reserved range for application */
#define SHT_HIUSER      0xffffffff      /* specific indexes */

struct elf32_rel {
  elf32_addr      r_offset;       /* Location to be relocated. */
  elf32_word      r_info;         /* Relocation type and symbol index. */
};

struct elf32_sym {
  elf32_word      st_name;        /* String table index of name. */
  elf32_addr      st_value;       /* Symbol value. */
  elf32_word      st_size;        /* Size of associated object. */
  unsigned char   st_info;        /* Type and binding information. */
  unsigned char   st_other;       /* Reserved (not used). */
  elf32_half      st_shndx;       /* Section index of symbol. */
};

#define ELF32_R_SYM(info)       ((info) >> 8)
#define ELF32_R_TYPE(info)      ((unsigned char)(info))

struct relevant_section {
  unsigned char number;
  unsigned int offset;
  char *address;
};

char elfloader_unknown[30];	/* Name that caused link error. */

static struct relevant_section bss, data, rodata, text;

const static unsigned char elf_magic_header[] =
  {0x7f, 0x45, 0x4c, 0x46,  /* 0x7f, 'E', 'L', 'F' */
   0x01,                    /* Only 32-bit objects. */
   0x01,                    /* Only LSB data. */
   0x01,                    /* Only ELF version 1. */
  };

/*---------------------------------------------------------------------------*/
static void *
find_local_symbol(const char *symbol,
		  unsigned int symtab, unsigned short symtabsize,
		  unsigned int strtab)
{
  struct elf32_sym s;
  unsigned int a;
  char name[30];
  struct relevant_section *sect;
  
  for(a = symtab; a < symtab + symtabsize; a += sizeof(s)) {
    elfstore_read((char *)&s, a, sizeof(s));
    
    if(s.st_name != 0) {
      elfstore_read(name, strtab + s.st_name, sizeof(name));
      if(strcmp(name, symbol) == 0) {
	if(s.st_shndx == bss.number) {
	  sect = &bss;
	} else if(s.st_shndx == data.number) {
	  sect = &data;
	} else if(s.st_shndx == text.number) {
	  sect = &text;
	} else {
	  return NULL;
	}
	return &(sect->address[s.st_value]);
      }
    }
  }
  return NULL;
}
/*---------------------------------------------------------------------------*/
static int
relocate_section(unsigned int section, unsigned short size,
		 unsigned int sectionaddr,
		 char *sectionbase,
		 unsigned int strs,
		 unsigned int strtab,
		 unsigned int symtab, unsigned short symtabsize,
		 unsigned char using_relas)
{
  /* sectionbase added; runtime start address of current section */
  struct elf32_rela rela; /* Now used both for rel and rela data! */
  int rel_size = 0;
  struct elf32_sym s;
  unsigned int a;
  char name[30];
  char *addr;
  struct relevant_section *sect;
  
  /* determine correct relocation entry sizes */
  if(using_relas) {
    rel_size = sizeof(struct elf32_rela);
  } else {
    rel_size = sizeof(struct elf32_rel);
  }
  
  for(a = section; a < section + size; a += rel_size) {
    elfstore_read((char *)&rela, a, rel_size);
    elfstore_read((char *)&s, symtab + sizeof(struct elf32_sym) * ELF32_R_SYM(rela.r_info), sizeof(s));
    
    if(s.st_name != 0) {
      elfstore_read(name, strtab + s.st_name, sizeof(name));
      
      PRINTF("name: %s\n", name);
      addr = (char *)symtab_lookup(name);
      
      if(addr == NULL) {
	PRINTF("name not found in global: %s\n", name);
	addr = find_local_symbol(name, symtab, symtabsize, strtab);
	PRINTF("found address %p\n", addr);
      }

      if(addr == NULL) {
	if(s.st_shndx == bss.number) {
	  sect = &bss;
	} else if(s.st_shndx == data.number) {
	  sect = &data;
	} else if(s.st_shndx == rodata.number) {
	  sect = &rodata;
	} else if(s.st_shndx == text.number) {
	  sect = &text;
	} else {
	  PRINTF("elfloader unknown name: '%30s'\n", name);
	  memcpy(elfloader_unknown, name, sizeof(elfloader_unknown));
	  elfloader_unknown[sizeof(elfloader_unknown) - 1] = 0;
	  return ELFLOADER_SYMBOL_NOT_FOUND;
	}
	addr = sect->address;
      }
    } else {
      if(s.st_shndx == bss.number) {
	sect = &bss;
      } else if(s.st_shndx == data.number) {
	sect = &data;
      } else if(s.st_shndx == rodata.number) {
	sect = &rodata;
      } else if(s.st_shndx == text.number) {
	sect = &text;
      } else {
	return ELFLOADER_SEGMENT_NOT_FOUND;
      }
      
      addr = sect->address;
    }
    
    if (!using_relas) {
      /* convert rel to rela by setting offset */
      elfstore_read(&rela.r_addend, sectionaddr + rela.r_offset, 4);
    }
    
    elfloader_arch_relocate(sectionaddr, sectionbase, &rela, addr);
  }
  return ELFLOADER_OK;
}
/*---------------------------------------------------------------------------*/
void
elfloader_init(void)
{
  elfloader_loaded_load = (void (*)(void))NULL;
  elfloader_loaded_unload = (void (*)(void))NULL;
}
/*---------------------------------------------------------------------------*/
#if 1
static void
print_bytes(unsigned char *ptr, int num)
{
  int i;
  for(i = 0; i < num; ++i) {
    PRINTF(" %x ", ptr[i]);
    if(i == num - 1) {
      PRINTF("\n");
    } else {
      PRINTF(", ");
    }
  }
}
#endif /* 0 */
/*---------------------------------------------------------------------------*/
int
elfloader_load()
{
  struct elf32_ehdr ehdr;
  struct elf32_shdr shdr;
  struct elf32_shdr strtable;
  unsigned int strs;
  unsigned int shdrptr;
  unsigned int nameptr;
  char name[12];
  
  int i;
  unsigned short shdrnum, shdrsize;
  
  unsigned char using_relas = -1;
  unsigned short textoff = 0, textsize, textrelaoff = 0, textrelasize;
  unsigned short dataoff = 0, datasize, datarelaoff = 0, datarelasize;
  unsigned short rodataoff = 0, rodatasize, rodatarelaoff = 0, rodatarelasize;
  unsigned short symtaboff = 0, symtabsize;
  unsigned short strtaboff = 0, strtabsize;
  unsigned short bsssize = 0;
  
  void (*elf_function)(void);
  int ret;
  
  elfloader_loaded_load = (void (*)(void))NULL;
  elfloader_loaded_unload = (void (*)(void))NULL;
  
  PRINTF("elfloader_load() called\n");
  
  elfloader_unknown[0] = 0;

  /* The ELF header is located at the start of the buffer. */
  elfstore_read((char*)&ehdr, 0, sizeof(ehdr));
  
  /*  print_chars(ehdr.e_ident, sizeof(elf_magic_header));
      print_chars(elf_magic_header, sizeof(elf_magic_header));*/
  /* Make sure that we have a correct and compatible ELF header. */
  if(memcmp(ehdr.e_ident, elf_magic_header, sizeof(elf_magic_header)) != 0) {
    PRINTF("ELF header problems\n");
    return ELFLOADER_BAD_ELF_HEADER;
  }
  
  /* Grab the section header. */
  shdrptr = ehdr.e_shoff;
  elfstore_read((char*)&shdr, shdrptr, sizeof(shdr));
  
  /* Get the size and number of entries of the section header. */
  shdrsize = ehdr.e_shentsize;
  shdrnum = ehdr.e_shnum;
  
  /* The string table section: holds the names of the sections. */
  elfstore_read((char *)&strtable, ehdr.e_shoff + shdrsize * ehdr.e_shstrndx, sizeof(strtable));
  
  /* Get a pointer to the actual table of strings. This table holds
     the names of the sections, not the names of other symbols in the
     file (these are in the sybtam section). */
  strs = strtable.sh_offset;
  
  /* Go through all sections and pick out the relevant ones. The
     ".text" segment holds the actual code from the ELF file, the
     ".data" segment contains initialized data, the ".bss" segment
     holds the size of the unitialized data segment. The ".rel[a].text"
     and ".rel[a].data" segments contains relocation information for the
     contents of the ".text" and ".data" segments, respectively. The
     ".symtab" segment contains the symbol table for this file. The
     ".strtab" segment points to the actual string names used by the
     symbol table.
     
     In addition to grabbing pointers to the relevant sections, we
     also save the section number for resolving addresses in the
     relocator code.
  */
  
  
  /* Initialize the segment sizes to zero so that we can check if
     their sections was found in the file or not. */
  textsize = textrelasize = datasize = datarelasize =
    rodatasize = rodatarelasize = symtabsize = strtabsize = 0;
  
  bss.number = data.number = rodata.number = text.number = -1;
  
  shdrptr = ehdr.e_shoff;
  for(i = 0; i < shdrnum; ++i) {
    elfstore_read((char *)&shdr, shdrptr, sizeof(shdr));
    
    /* The name of the section is contained in the strings table. */
    nameptr = strs + shdr.sh_name;
    elfstore_read(name, nameptr, sizeof(name));
    
    /* Match the name of the section with a predefined set of names
       (.text, .data, .bss, .rela.text, .rela.data, .symtab, and
       .strtab). */
    /* added support for .rodata, .rel.text and .rel.data). */
    
    if(strncmp(name, ".text", 5) == 0) {
      textoff = shdr.sh_offset;
      textsize = shdr.sh_size;
      text.number = i;
      text.offset = textoff;
    } else if(strncmp(name, ".rel.text", 9) == 0) {
      using_relas = 0;
      textrelaoff = shdr.sh_offset;
      textrelasize = shdr.sh_size;
    } else if(strncmp(name, ".rela.text", 10) == 0) {
      using_relas = 1;
      textrelaoff = shdr.sh_offset;
      textrelasize = shdr.sh_size;
    } else if(strncmp(name, ".data", 5) == 0) {
      dataoff = shdr.sh_offset;
      datasize = shdr.sh_size;
      data.number = i;
      data.offset = dataoff;
    } else if(strncmp(name, ".rodata", 7) == 0) {
      /* read-only data handled the same way as regular text section */
      rodataoff = shdr.sh_offset;
      rodatasize = shdr.sh_size;
      rodata.number = i;
      rodata.offset = rodataoff;
    } else if(strncmp(name, ".rel.rodata", 11) == 0) {
      /* using elf32_rel instead of rela */
      using_relas = 0;
      rodatarelaoff = shdr.sh_offset;
      rodatarelasize = shdr.sh_size;
    } else if(strncmp(name, ".rela.rodata", 12) == 0) {
      using_relas = 1;
      rodatarelaoff = shdr.sh_offset;
      rodatarelasize = shdr.sh_size;
    } else if(strncmp(name, ".rel.data", 9) == 0) {
      /* using elf32_rel instead of rela */
      using_relas = 0;
      datarelaoff = shdr.sh_offset;
      datarelasize = shdr.sh_size;
    } else if(strncmp(name, ".rela.data", 10) == 0) {
      using_relas = 1;
      datarelaoff = shdr.sh_offset;
      datarelasize = shdr.sh_size;
    } else if(strncmp(name, ".symtab", 7) == 0) {
      symtaboff = shdr.sh_offset;
      symtabsize = shdr.sh_size;
    } else if(strncmp(name, ".strtab", 7) == 0) {
      strtaboff = shdr.sh_offset;
      strtabsize = shdr.sh_size;
    } else if(strncmp(name, ".bss", 4) == 0) {
      bsssize = shdr.sh_size;
      bss.number = i;
      bss.offset = 0;
    }
    
    /* Move on to the next section header. */
    shdrptr += shdrsize;
  }
  
  if(symtabsize == 0) {
    return ELFLOADER_NO_SYMTAB;
  }
  if(strtabsize == 0) {
    return ELFLOADER_NO_STRTAB;
  }
  if(textsize == 0) {
    return ELFLOADER_NO_TEXT;
  }
  
  bss.address = (char *)elfloader_arch_allocate_ram(bsssize + datasize);
  data.address = (char *)bss.address + bsssize;
  text.address = (char *)elfloader_arch_allocate_rom(textsize + rodatasize);
  rodata.address = (char *)text.address + textsize;
  
  PRINTF("bss base address: bss.address = 0x%08x\n", bss.address);
  PRINTF("data base address: data.address = 0x%08x\n", data.address);
  PRINTF("text base address: text.address = 0x%08x\n", text.address);
  PRINTF("rodata base address: rodata.address = 0x%08x\n", rodata.address);
  
  /* If we have text segment relocations, we process them. */
  PRINTF("elfloader: relocate text\n");
  if(textrelasize > 0) {
    ret = relocate_section(textrelaoff, textrelasize,
			   textoff,
			   text.address,
			   strs,
			   strtaboff,
			   symtaboff, symtabsize, using_relas);
    if(ret != ELFLOADER_OK) {
      return ret;
    }
  }
  
  /* If we have any rodata segment relocations, we process them too. */
  PRINTF("elfloader: relocate rodata\n");
  if(rodatarelasize > 0) {
    ret = relocate_section(rodatarelaoff, rodatarelasize,
			   rodataoff,
			   rodata.address,
			   strs,
			   strtaboff,
			   symtaboff, symtabsize, using_relas);
    if(ret != ELFLOADER_OK) {
      PRINTF("elfloader: data failed\n");
      return ret;
    }
  }
  
  /* If we have any data segment relocations, we process them too. */
  PRINTF("elfloader: relocate data\n");
  if(datarelasize > 0) {
    ret = relocate_section(datarelaoff, datarelasize,
			   dataoff,
			   data.address,
			   strs,
			   strtaboff,
			   symtaboff, symtabsize, using_relas);
    if(ret != ELFLOADER_OK) {
      PRINTF("elfloader: data failed\n");
      return ret;
    }
  }
  
  /* Write text segment into flash and data segment into RAM. */
  if(textsize > 0) {
    elfloader_arch_write_rom(textoff, textsize, text.address);
  }
  
  if(rodatasize > 0) {
    elfloader_arch_write_rom(rodataoff, rodatasize, rodata.address);
  }
  
  memset(bss.address, 0, bsssize);
  elfstore_read(data.address, dataoff, datasize);
  
  PRINTF("elfloader: load() search\n");
  elf_function = (void (*)(void)) find_local_symbol("load", symtaboff, symtabsize, strtaboff);
  if(elf_function != NULL) {
    PRINTF("elfloader: load() found\n");
    elfloader_loaded_load = (void (*)(void))elf_function;
    /* print_bytes((char*) elfloader_loaded_load, 10); */
  } else {
    PRINTF("elfloader: load() found\n");
    return ELFLOADER_NO_STARTPOINT;
  }
  
  PRINTF("elfloader: unload() search\n");
  elf_function = (void (*)(void)) find_local_symbol("unload", symtaboff, symtabsize, strtaboff);
  if(elf_function != NULL) {
    PRINTF("elfloader: unload() found\n");
    elfloader_loaded_unload = (void (*)(void))elf_function;
    /* print_bytes((char*) elfloader_loaded_unload, 10); */
  } else {
    elfloader_loaded_unload = NULL;
    PRINTF("elfloader: no unload() found\n");
    return ELFLOADER_NO_STARTPOINT;
  }
  
  return ELFLOADER_OK;
}

/*---------------------------------------------------------------------------*/
