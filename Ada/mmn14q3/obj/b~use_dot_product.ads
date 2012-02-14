pragma Ada_95;
with System;
package ada_main is
   pragma Warnings (Off);

   gnat_argc : Integer;
   gnat_argv : System.Address;
   gnat_envp : System.Address;

   pragma Import (C, gnat_argc);
   pragma Import (C, gnat_argv);
   pragma Import (C, gnat_envp);

   gnat_exit_status : Integer;
   pragma Import (C, gnat_exit_status);

   GNAT_Version : constant String :=
                    "GNAT Version: 4.4.6" & ASCII.NUL;
   pragma Export (C, GNAT_Version, "__gnat_version");

   Ada_Main_Program_Name : constant String := "_ada_use_dot_product" & ASCII.NUL;
   pragma Export (C, Ada_Main_Program_Name, "__gnat_ada_main_program_name");

   procedure adafinal;
   pragma Export (C, adafinal, "adafinal");

   procedure adainit;
   pragma Export (C, adainit, "adainit");

   procedure Break_Start;
   pragma Import (C, Break_Start, "__gnat_break_start");

   function main
     (argc : Integer;
      argv : System.Address;
      envp : System.Address)
      return Integer;
   pragma Export (C, main, "main");

   type Version_32 is mod 2 ** 32;
   u00001 : constant Version_32 := 16#2f93c8dc#;
   u00002 : constant Version_32 := 16#4b33036a#;
   u00003 : constant Version_32 := 16#03570e27#;
   u00004 : constant Version_32 := 16#1c12806f#;
   u00005 : constant Version_32 := 16#a9d19700#;
   u00006 : constant Version_32 := 16#96410e68#;
   u00007 : constant Version_32 := 16#51283ab9#;
   u00008 : constant Version_32 := 16#e799a3c1#;
   u00009 : constant Version_32 := 16#6ad13d41#;
   u00010 : constant Version_32 := 16#496d6bfd#;
   u00011 : constant Version_32 := 16#9c7dd3ea#;
   u00012 : constant Version_32 := 16#df55302f#;
   u00013 : constant Version_32 := 16#2ea84b20#;
   u00014 : constant Version_32 := 16#2c7b66c6#;
   u00015 : constant Version_32 := 16#b6c89fbe#;
   u00016 : constant Version_32 := 16#430a8d84#;
   u00017 : constant Version_32 := 16#352d93cc#;
   u00018 : constant Version_32 := 16#eaa55474#;
   u00019 : constant Version_32 := 16#9201cee0#;
   u00020 : constant Version_32 := 16#e3d85f73#;
   u00021 : constant Version_32 := 16#fcfb2939#;
   u00022 : constant Version_32 := 16#d1fec254#;
   u00023 : constant Version_32 := 16#1a63fe0c#;
   u00024 : constant Version_32 := 16#a9f5773f#;
   u00025 : constant Version_32 := 16#5b8b9839#;
   u00026 : constant Version_32 := 16#cfea76ef#;
   u00027 : constant Version_32 := 16#55ef7c79#;
   u00028 : constant Version_32 := 16#32c35ddc#;
   u00029 : constant Version_32 := 16#b871c253#;
   u00030 : constant Version_32 := 16#5b0a42fd#;
   u00031 : constant Version_32 := 16#9e37526b#;
   u00032 : constant Version_32 := 16#ad9b204c#;
   u00033 : constant Version_32 := 16#9c49ee35#;
   u00034 : constant Version_32 := 16#b53be4c7#;
   u00035 : constant Version_32 := 16#1faccaca#;
   u00036 : constant Version_32 := 16#743d3d0d#;
   u00037 : constant Version_32 := 16#7457b7b6#;
   u00038 : constant Version_32 := 16#ccde3404#;
   u00039 : constant Version_32 := 16#f020f847#;
   u00040 : constant Version_32 := 16#2c57c517#;
   u00041 : constant Version_32 := 16#ffc4bcd0#;
   u00042 : constant Version_32 := 16#a69cad5c#;
   u00043 : constant Version_32 := 16#300a43f3#;
   u00044 : constant Version_32 := 16#d4ede0a0#;
   u00045 : constant Version_32 := 16#99c8a881#;
   u00046 : constant Version_32 := 16#620a177c#;
   u00047 : constant Version_32 := 16#e1e7b9d6#;
   u00048 : constant Version_32 := 16#17b86634#;
   u00049 : constant Version_32 := 16#842c78ec#;
   u00050 : constant Version_32 := 16#db027b4b#;
   u00051 : constant Version_32 := 16#b5095267#;

   pragma Export (C, u00001, "use_dot_productB");
   pragma Export (C, u00002, "system__standard_libraryB");
   pragma Export (C, u00003, "system__standard_libraryS");
   pragma Export (C, u00004, "dot_productB");
   pragma Export (C, u00005, "dot_productS");
   pragma Export (C, u00006, "gnatS");
   pragma Export (C, u00007, "gnat__ioB");
   pragma Export (C, u00008, "gnat__ioS");
   pragma Export (C, u00009, "system__secondary_stackB");
   pragma Export (C, u00010, "system__secondary_stackS");
   pragma Export (C, u00011, "adaS");
   pragma Export (C, u00012, "systemS");
   pragma Export (C, u00013, "system__parametersB");
   pragma Export (C, u00014, "system__parametersS");
   pragma Export (C, u00015, "system__soft_linksB");
   pragma Export (C, u00016, "system__soft_linksS");
   pragma Export (C, u00017, "ada__exceptionsB");
   pragma Export (C, u00018, "ada__exceptionsS");
   pragma Export (C, u00019, "ada__exceptions__last_chance_handlerB");
   pragma Export (C, u00020, "ada__exceptions__last_chance_handlerS");
   pragma Export (C, u00021, "system__exception_tableB");
   pragma Export (C, u00022, "system__exception_tableS");
   pragma Export (C, u00023, "system__htableB");
   pragma Export (C, u00024, "system__htableS");
   pragma Export (C, u00025, "system__exceptionsB");
   pragma Export (C, u00026, "system__exceptionsS");
   pragma Export (C, u00027, "system__storage_elementsB");
   pragma Export (C, u00028, "system__storage_elementsS");
   pragma Export (C, u00029, "system__string_opsB");
   pragma Export (C, u00030, "system__string_opsS");
   pragma Export (C, u00031, "system__string_ops_concat_3B");
   pragma Export (C, u00032, "system__string_ops_concat_3S");
   pragma Export (C, u00033, "system__tracebackB");
   pragma Export (C, u00034, "system__tracebackS");
   pragma Export (C, u00035, "system__unsigned_typesS");
   pragma Export (C, u00036, "system__wch_conB");
   pragma Export (C, u00037, "system__wch_conS");
   pragma Export (C, u00038, "system__wch_stwB");
   pragma Export (C, u00039, "system__wch_stwS");
   pragma Export (C, u00040, "system__wch_cnvB");
   pragma Export (C, u00041, "system__wch_cnvS");
   pragma Export (C, u00042, "interfacesS");
   pragma Export (C, u00043, "system__wch_jisB");
   pragma Export (C, u00044, "system__wch_jisS");
   pragma Export (C, u00045, "system__traceback_entriesB");
   pragma Export (C, u00046, "system__traceback_entriesS");
   pragma Export (C, u00047, "system__stack_checkingB");
   pragma Export (C, u00048, "system__stack_checkingS");
   pragma Export (C, u00049, "system__memoryB");
   pragma Export (C, u00050, "system__memoryS");
   pragma Export (C, u00051, "system__crtlS");

   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  gnat%s
   --  gnat.io%s
   --  gnat.io%b
   --  interfaces%s
   --  system%s
   --  system.htable%s
   --  system.htable%b
   --  system.parameters%s
   --  system.parameters%b
   --  system.crtl%s
   --  system.standard_library%s
   --  system.exceptions%s
   --  system.exceptions%b
   --  system.storage_elements%s
   --  system.storage_elements%b
   --  system.secondary_stack%s
   --  system.stack_checking%s
   --  system.stack_checking%b
   --  system.string_ops%s
   --  system.string_ops%b
   --  system.string_ops_concat_3%s
   --  system.string_ops_concat_3%b
   --  system.traceback%s
   --  system.traceback%b
   --  system.traceback_entries%s
   --  system.traceback_entries%b
   --  ada.exceptions%s
   --  ada.exceptions.last_chance_handler%s
   --  system.soft_links%s
   --  system.soft_links%b
   --  ada.exceptions.last_chance_handler%b
   --  system.secondary_stack%b
   --  system.exception_table%s
   --  system.exception_table%b
   --  system.memory%s
   --  system.memory%b
   --  system.standard_library%b
   --  system.unsigned_types%s
   --  system.wch_con%s
   --  system.wch_con%b
   --  system.wch_cnv%s
   --  system.wch_jis%s
   --  system.wch_jis%b
   --  system.wch_cnv%b
   --  system.wch_stw%s
   --  system.wch_stw%b
   --  ada.exceptions%b
   --  dot_product%s
   --  dot_product%b
   --  use_dot_product%b
   --  END ELABORATION ORDER

end ada_main;
