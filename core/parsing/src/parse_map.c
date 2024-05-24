#include "../inc/parser.h"

/*
	@brief Checks if the character is a valid player character
	@param	c The character to check
	@return true if the character is a valid player character, false otherwise
*/
bool	is_valid_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');

}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n');
}

bool validate_player(char *str) 
{
    bool found;
	
	found = false;
    while (*str) 
	{
        if (is_valid_player_char(*str))
		{
            if (found)
                return (false);
            found = true;
        }
        str++;
    }
    return (found);
}

bool parse_map(int map_fd, char ***map)
{
	return (true);
}
