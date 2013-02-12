pragma Ada_95;
pragma Source_File_Name (ada_main, Spec_File_Name => "b~banking.ads");
pragma Source_File_Name (ada_main, Body_File_Name => "b~banking.adb");

with System.Restrictions;

package body ada_main is
   pragma Warnings (Off);

   procedure Do_Finalize;
   pragma Import (C, Do_Finalize, "system__standard_library__adafinal");

   Local_Priority_Specific_Dispatching : constant String := "";
   Local_Interrupt_States : constant String := "";

   procedure adainit is
      E17 : Boolean; pragma Import (Ada, E17, "system__secondary_stack_E");
      E13 : Boolean; pragma Import (Ada, E13, "system__soft_links_E");
      E23 : Boolean; pragma Import (Ada, E23, "system__exception_table_E");
      E81 : Boolean; pragma Import (Ada, E81, "ada__io_exceptions_E");
      E59 : Boolean; pragma Import (Ada, E59, "ada__tags_E");
      E57 : Boolean; pragma Import (Ada, E57, "ada__streams_E");
      E83 : Boolean; pragma Import (Ada, E83, "interfaces__c_E");
      E74 : Boolean; pragma Import (Ada, E74, "system__finalization_root_E");
      E85 : Boolean; pragma Import (Ada, E85, "system__os_lib_E");
      E76 : Boolean; pragma Import (Ada, E76, "system__finalization_implementation_E");
      E72 : Boolean; pragma Import (Ada, E72, "ada__finalization_E");
      E90 : Boolean; pragma Import (Ada, E90, "ada__finalization__list_controller_E");
      E88 : Boolean; pragma Import (Ada, E88, "system__file_control_block_E");
      E70 : Boolean; pragma Import (Ada, E70, "system__file_io_E");
      E56 : Boolean; pragma Import (Ada, E56, "ada__text_io_E");
      E05 : Boolean; pragma Import (Ada, E05, "accounts_E");
      E47 : Boolean; pragma Import (Ada, E47, "bank_E");

      Main_Priority : Integer;
      pragma Import (C, Main_Priority, "__gl_main_priority");
      Time_Slice_Value : Integer;
      pragma Import (C, Time_Slice_Value, "__gl_time_slice_val");
      WC_Encoding : Character;
      pragma Import (C, WC_Encoding, "__gl_wc_encoding");
      Locking_Policy : Character;
      pragma Import (C, Locking_Policy, "__gl_locking_policy");
      Queuing_Policy : Character;
      pragma Import (C, Queuing_Policy, "__gl_queuing_policy");
      Task_Dispatching_Policy : Character;
      pragma Import (C, Task_Dispatching_Policy, "__gl_task_dispatching_policy");
      Priority_Specific_Dispatching : System.Address;
      pragma Import (C, Priority_Specific_Dispatching, "__gl_priority_specific_dispatching");
      Num_Specific_Dispatching : Integer;
      pragma Import (C, Num_Specific_Dispatching, "__gl_num_specific_dispatching");
      Interrupt_States : System.Address;
      pragma Import (C, Interrupt_States, "__gl_interrupt_states");
      Num_Interrupt_States : Integer;
      pragma Import (C, Num_Interrupt_States, "__gl_num_interrupt_states");
      Unreserve_All_Interrupts : Integer;
      pragma Import (C, Unreserve_All_Interrupts, "__gl_unreserve_all_interrupts");
      Zero_Cost_Exceptions : Integer;
      pragma Import (C, Zero_Cost_Exceptions, "__gl_zero_cost_exceptions");
      Detect_Blocking : Integer;
      pragma Import (C, Detect_Blocking, "__gl_detect_blocking");
      Default_Stack_Size : Integer;
      pragma Import (C, Default_Stack_Size, "__gl_default_stack_size");
      Leap_Seconds_Support : Integer;
      pragma Import (C, Leap_Seconds_Support, "__gl_leap_seconds_support");

      procedure Install_Handler;
      pragma Import (C, Install_Handler, "__gnat_install_handler");

      Handler_Installed : Integer;
      pragma Import (C, Handler_Installed, "__gnat_handler_installed");
   begin
      Main_Priority := -1;
      Time_Slice_Value := -1;
      WC_Encoding := 'b';
      Locking_Policy := ' ';
      Queuing_Policy := ' ';
      Task_Dispatching_Policy := ' ';
      System.Restrictions.Run_Time_Restrictions :=
        (Set =>
          (False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False, False, False, 
           False, False, False, False, False, False),
         Value => (0, 0, 0, 0, 0, 0, 0),
         Violated =>
          (False, False, True, True, False, False, False, True, 
           True, True, False, False, False, False, False, True, 
           True, False, True, True, True, True, True, True, 
           False, False, True, False, True, False, False, True, 
           False, False, True, False, False, False, True, False, 
           False, True, False, False, False, False, False, False, 
           False, False, True, True, True, False, False, True, 
           False, True, True, False, True, True, True, False, 
           False, False, False, False, False, False),
         Count => (0, 0, 0, 0, 0, 0, 0),
         Unknown => (False, False, False, False, False, False, False));
      Priority_Specific_Dispatching :=
        Local_Priority_Specific_Dispatching'Address;
      Num_Specific_Dispatching := 0;
      Interrupt_States := Local_Interrupt_States'Address;
      Num_Interrupt_States := 0;
      Unreserve_All_Interrupts := 0;
      Zero_Cost_Exceptions := 1;
      Detect_Blocking := 0;
      Default_Stack_Size := -1;
      Leap_Seconds_Support := 0;

      if Handler_Installed = 0 then
         Install_Handler;
      end if;

      System.Soft_Links'Elab_Body;
      E13 := True;
      System.Secondary_Stack'Elab_Body;
      E17 := True;
      System.Exception_Table'Elab_Body;
      E23 := True;
      Ada.Io_Exceptions'Elab_Spec;
      E81 := True;
      Ada.Tags'Elab_Spec;
      Ada.Streams'Elab_Spec;
      E57 := True;
      Interfaces.C'Elab_Spec;
      E83 := True;
      System.Finalization_Root'Elab_Spec;
      E74 := True;
      System.Os_Lib'Elab_Body;
      E85 := True;
      System.Finalization_Implementation'Elab_Spec;
      System.Finalization_Implementation'Elab_Body;
      E76 := True;
      Ada.Finalization'Elab_Spec;
      E72 := True;
      Ada.Finalization.List_Controller'Elab_Spec;
      E90 := True;
      System.File_Control_Block'Elab_Spec;
      E88 := True;
      System.File_Io'Elab_Body;
      E70 := True;
      Ada.Tags'Elab_Body;
      E59 := True;
      Ada.Text_Io'Elab_Spec;
      Ada.Text_Io'Elab_Body;
      E56 := True;
      Accounts'Elab_Spec;
      E05 := True;
      Bank'Elab_Spec;
      Bank'Elab_Body;
      E47 := True;
   end adainit;

   procedure adafinal is
   begin
      Do_Finalize;
   end adafinal;

   function main
     (argc : Integer;
      argv : System.Address;
      envp : System.Address)
      return Integer
   is
      procedure initialize (Addr : System.Address);
      pragma Import (C, initialize, "__gnat_initialize");

      procedure finalize;
      pragma Import (C, finalize, "__gnat_finalize");

      procedure Ada_Main_Program;
      pragma Import (Ada, Ada_Main_Program, "_ada_banking");

      SEH : aliased array (1 .. 2) of Integer;

      Ensure_Reference : aliased System.Address := Ada_Main_Program_Name'Address;
      pragma Volatile (Ensure_Reference);

   begin
      gnat_argc := argc;
      gnat_argv := argv;
      gnat_envp := envp;

      Initialize (SEH'Address);
      adainit;
      Break_Start;
      Ada_Main_Program;
      Do_Finalize;
      Finalize;
      return (gnat_exit_status);
   end;

--  BEGIN Object file/option list
   --   /home/solekiller/workspace/mm13q2/obj_debug/accounts.o
   --   /home/solekiller/workspace/mm13q2/obj_debug/bank.o
   --   /home/solekiller/workspace/mm13q2/obj_debug/banking.o
   --   -L/home/solekiller/workspace/mm13q2/obj_debug/
   --   -L/usr/lib/gcc/x86_64-linux-gnu/4.4/adalib/
   --   -shared
   --   -lgnat-4.4
--  END Object file/option list   

end ada_main;
