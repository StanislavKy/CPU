#include "assembler.h"

struct string* assembler_construct (file* asm_file, char* file_name)
{
    read_asm (file_name, asm_file);

    struct string* data = place_pointers (asm_file);

    deep_analize_array (asm_file, data);

    return data;
}

//=====================================================================================================
     
void deep_analize_array (file* asm_file, string* data)
{
    int   cmd_number = 0; 
    int   cmd_len    = 0;
    int   cmd_code   = 0;
    
    char* p_beg_str = nullptr;
    char* cmd_ptr   = nullptr;
    char* nmb_ptr   = nullptr;  
    
    char* tokes_arr = (char*) calloc (asm_file -> size_of_file, sizeof (char)); 
    assert (tokes_arr != nullptr)
    ;
    int  idx = 0;

    for (int i = 0; i < (asm_file -> number_line); i++)     // цикл по каждой структуре массива структур
    {
        p_beg_str = (data + i) -> beg_ptr;
      
        cmd_ptr   = strtok (p_beg_str, " ,\n,\0");
        nmb_ptr   = strtok (NULL," ,\n,\0");

        if (nmb_ptr != nullptr) /* if found a number*/
        {
            cmd_len     = nmb_ptr - cmd_ptr - 1;
            cmd_number  = atoi (nmb_ptr);

            char* cmd_buffer  = (char*) calloc (cmd_len + 1, sizeof (char)); // +1 for place /0 cause scrmp need /0
            assert (cmd_buffer != nullptr);

            for (int item = 0; item < cmd_len; item++) 
                cmd_buffer[item] = p_beg_str[item];
            
            cmd_buffer[cmd_len + 1] = '\0';

            cmd_code = assembling (cmd_buffer);

            free (cmd_buffer);
            cmd_buffer = nullptr;

            tokes_arr[idx] = cmd_code;
                idx++;
            tokes_arr[idx] = ' ';
                idx++;
            tokes_arr[idx] = (char) cmd_number;
                idx++;
            tokes_arr[idx] = ' ';
                idx++;
        }

        else
        {            
            cmd_len = (data + i) -> str_length;

            char* cmd_buffer = (char*) calloc (cmd_len + 1, sizeof (char));
            assert(cmd_buffer != nullptr);
            
            for (int item = 0; item < cmd_len; item++) 
                cmd_buffer[item] = p_beg_str[item];
            
            cmd_buffer[cmd_len + 1] = '\0';
            cmd_code = assembling (cmd_buffer);
            
            free (cmd_buffer);
            cmd_buffer = nullptr;   
            
            tokes_arr[idx] = cmd_code;
                idx++;
            tokes_arr[idx] = ' ';
                idx++;
        }
    }

    input_b_file (asm_file, tokes_arr);
    
    free (tokes_arr);
    tokes_arr = nullptr;
}

//=====================================================================================================

int assembling (char* cmd)
{
    using namespace my_commands;

    if (0) printf ("CACATB\n");
    
    get_command (pop, POP)
    get_command (add, ADD)
    get_command (sub, SUB)
    get_command (div, DIV)
    get_command (out, OUT)
    get_command (hlt, HLT)
    get_command (end, END)
    get_command (unknown_cmd, UNKNOWN_CMD)
    
    return -1;
}

//=====================================================================================================

void input_b_file (file* asm_file, char* tokes_arr)
{
    FILE* file = fopen ("../txt files/asm_binary", "wb");
    assert (file != nullptr);

    fwrite (tokes_arr, sizeof (char), asm_file -> size_of_file, file);

    fclose (file);
}

//=====================================================================================================

void assembler_destruct (char* asm_buffer, string* data)
{
    free (asm_buffer);
    asm_buffer = nullptr;
    
    free (data);
    data = nullptr;
}              

//=====================================================================================================