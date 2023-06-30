NAME = so_long

BONUS = so_long_bonus

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

BONUS_SRCS_DIR = ./bonus_srcs

BONUS_SRCS = $(wildcard $(BONUS_SRCS_DIR)/*.c)

OBJS_DIR = ./objs

OBJS = $(addprefix $(OBJS_DIR)/,$(notdir $(SRCS:.c=.o)))

BONUS_OBJS_DIR = ./bonus_objs

BONUS_OBJS = $(addprefix $(BONUS_OBJS_DIR)/,$(notdir $(BONUS_SRCS:.c=.o)))

MLX_GIT = https://github.com/codam-coding-college/MLX42

TESTER_GIT = https://github.com/augustobecker/so_long_tester

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(BONUS_OBJS_DIR):
	mkdir -p $(BONUS_OBJS_DIR)

$(NAME): $(LIBFT) $(OBJS_DIR) $(OBJS) $(MLX)
	$(CC) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC_GLFW)

$(BONUS): $(BONUS_OBJS_DIR) $(BONUS_OBJS) $(MLX) $(LIBFT)
	$(CC) -o $(BONUS) $(BONUS_OBJS) $(MLX) $(LIBFT) $(INC_GLFW)

$(MLX):
	cd $(MLX_DIR) && cmake -B build && cmake --build build -j4

$(LIBFT):
	if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone https://github.com/Kingsolomon445/42_libft libft; \
	fi
	make -C $(LIBFT_DIR) all

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BONUS_OBJS_DIR)/%.o: $(BONUS_SRCS_DIR)/%.c
	$(CC) -c $(CFLAGS) $< -o $@

bonus:	$(BONUS)

clean:
	$(RM) $(OBJS_DIR)
	$(RM) $(BONUS_OBJS_DIR)
	$(RM) $(MLX_BUILD_DIR)
	cd $(LIBFT_DIR) && make clean

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
	cd $(LIBFT_DIR) && make fclean

re:	fclean all

mlx:
	git clone $(MLX_GIT)

dep:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install cmake
	brew install glfw

test:
	git clone $(TESTER_GIT)

.PHONY:	all	clean fclean re bonus test dep mlx
