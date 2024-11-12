# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 16:00:57 by guillaumebe       #+#    #+#              #
#    Updated: 2024/11/12 16:29:42 by gbeaudoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################### COLORS #####################################

RESET		:=	\e[0m
BOLD		:=	\e[1m
DIM		:=	\e[2m
ITAL		:=	\e[3m
UNDERLINE	:=	\e[4m

BLACK		:=	\e[30m
GRAY		:=	\e[90m
RED		:=	\e[31m
GREEN		:=	\e[32m
YELLOW		:=	\e[33m
ORANGE		:=	\e[38;5;208m
BLUE		:=	\e[34m
PURPLE		:=	\e[35m
PINK		:=	\033[38;2;255;182;193m
CYAN		:=	\e[36m



################################### BASICS ###################################

NAME		=	cub3d

LIBFT = libft/
MINILIBX = minilibx-linux/

CC		=	cc
CFLAGS	=	-g3 -Wall -Wextra -Werror -I $(INC) -MMD -MP
INC		=	include/
LIBC	=	ar -rcs
RM		=	rm -rf

MLXFLAGS	=	-lXext -lX11 -lm

################################### SOURCES ###################################

INIT_DIR 	= 	init/
INIT_FILES	= 	init.c
					
MLX_DIR 	= 	mlx/
MLX_FILES	= 	mlx.c

MOVEMENT_DIR 	= 	movement/
MOVEMENT_FILES	= 	player_mov.c rotation.c

OTHER_DIR 	=	other/
OTHER_FILES	=	error.c main.c utils.c

PARSING_DIR 	= 	parsing/
PARSING_FILES	= 	parse_map.c parsing.c verify_map.c

RAYCASTING_DIR 	= 	raycasting/
RAYCASTING_FILES	= 	raycasting_follow.c raycasting.c

######################## COMBINE DIRECTORIES AND FILES ########################

SRC_DIR		= src/

SRC_NAMES	= $(addprefix $(INIT_DIR), $(INIT_FILES)) \
			$(addprefix $(MLX_DIR), $(MLX_FILES)) \
			$(addprefix $(MOVEMENT_DIR), $(MOVEMENT_FILES)) \
			$(addprefix $(OTHER_DIR), $(OTHER_FILES)) \
			$(addprefix $(PARSING_DIR), $(PARSING_FILES)) \
			$(addprefix $(RAYCASTING_DIR), $(RAYCASTING_FILES)) 

OBJ_DIR		= obj/

OBJ_NAMES	= $(SRC_NAMES:.c=.o)

OBJ_FOLDERS	= $(addprefix $(OBJ_DIR), $(INIT_DIR)) \
			$(addprefix $(OBJ_DIR), $(MLX_DIR))	\
			$(addprefix $(OBJ_DIR), $(MOVEMENT_DIR))	\
			$(addprefix $(OBJ_DIR), $(OTHER_DIR))	\
			$(addprefix $(OBJ_DIR), $(PARSING_DIR))	\
			$(addprefix $(OBJ_DIR), $(RAYCASTING_DIR))	

OBJ		= $(addprefix $(OBJ_DIR), $(OBJ_NAMES))

DEP			=	$(OBJ:.o=.d)

#################################### MANDATORY ####################################


$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			@mkdir -p $(dir $@)
			@printf "$(ITAL)$(GREEN)Compiling: $(RESET)$(ITAL)$<\n"
			@$(CC) $(CFLAGS) -I$(INC) -c $< -o $@ -MF $(@:.o=.d)

# link .o files to the library
$(NAME):	$(OBJ)	
			@make -C $(LIBFT)
			@make -C $(MINILIBX)
			@cp $(MINILIBX)/libmlx.a .
			@cp $(LIBFT)/libft.a .
			@printf "\n $(BOLD)$(YELLOW)MiniLibX and Libft ready! $(RESET)\n"
			@printf "$(RESET)$(BOLD)$(CYAN)[Cub3d]:\t$(RESET)"
			@$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -L$(MINILIBX) -lmlx -L$(LIBFT) -lft -o $(NAME)
			@printf "$(PINK) ./Cub3d ready to play $(RESET)\n"

-include $(DEP)

all:		$(NAME)


#################################### RULES ####################################

clean:
		@$(RM) $(OBJ_DIR)
		@make clean -C $(MINILIBX) $(MAKEFLAGS)
		@make clean -C $(LIBFT) $(MAKEFLAGS)
		@printf "$(BOLD)$(PINK)[fdf]: $(RESET)$(PINK)object files $(RESET)\t\t=> CLEANED! \n\n"

fclean: 	clean
			@$(RM) $(NAME) $(BONUS)
			@$(RM) $(MINILIBX)/libmlx.a $(LIBFT)/libft.a
			@$(RM) libmlx.a libft.a
			@printf "$(BOLD)$(BLUE)[MiniLibX]: $(RESET)$(BLUE)exec. files $(RESET)\t=> CLEANED! \n\n"
			@printf "$(BOLD)$(PURPLE)[LIBFT]: $(RESET)$(PURPLE)exec. files $(RESET)\t=> CLEANED! \n\n"
			@printf "$(BOLD)$(BRIGHT_PURPLE)[Cub3d]: $(RESET)$(BRIGHT_PURPLE)exec. files $(RESET)\t=> CLEANED! \n\n"

re:		fclean all
			@printf "\n\n $(BOLD)$(YELLOW)Cleaning done! $(RESET)\n"
			
.PHONY:		all clean fclean re bonus
