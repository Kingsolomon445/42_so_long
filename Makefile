NAME = so_long

CC = cc

CFLAGS = -Wall -Wextra -Werror

INC_GLFW = -lglfw -L "$(HOME)/.brew/Cellar/glfw/3.3.8/lib/"

MLX_DIR = ./MLX42

MLX_BUILD_DIR = $(MLX_DIR)/build

MLX = $(MLX_BUILD_DIR)/libmlx42.a

LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

RM = rm -rf

SRCS_DIR = ./srcs

SRCS = $(wildcard $(SRCS_DIR)/*.c)

OBJS_DIR = ./objs

OBJS = $(addprefix $(OBJS_DIR)/,$(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(OBJS) $(MLX) $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC_GLFW)

$(MLX):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(LIBFT):
	cd $(LIBFT_DIR) && make all

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS_DIR)
	$(RM) $(MLX_BUILD_DIR)
	cd $(LIBFT_DIR) && make clean

fclean:	clean
	$(RM) $(NAME)
	cd $(LIBFT_DIR) && make fclean

re:	fclean all

.PHONY:	all	clean fclean re