# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llapage <llapage@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/06 17:38:39 by mde-clee          #+#    #+#              #
#    Updated: 2023/09/04 01:30:06 by mde-clee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

SOURCES			=	ft_atoi.c			\
					ft_bzero.c			\
					ft_calloc.c			\
					ft_isalnum.c		\
					ft_isalpha.c		\
					ft_isascii.c		\
					ft_isdigit.c		\
					ft_isprint.c		\
					ft_itoa.c			\
					ft_memchr.c			\
					ft_memcmp.c			\
					ft_memcpy.c			\
					ft_memmove.c		\
					ft_memset.c			\
					ft_putchar_fd.c		\
					ft_putendl_fd.c		\
					ft_putnbr_fd.c		\
					ft_putstr_fd.c		\
					ft_split.c			\
					ft_strchr.c			\
					ft_strdup.c			\
					ft_striteri.c		\
					ft_strjoin.c		\
					ft_strlcat.c		\
					ft_strlcpy.c		\
					ft_strlen.c			\
					ft_strmapi.c		\
					ft_strncmp.c		\
					ft_strnstr.c		\
					ft_strrchr.c		\
					ft_strtrim.c		\
					ft_substr.c			\
					ft_tolower.c		\
					ft_toupper.c

BONUS_SOURCES	=	ft_lstadd_back.c	\
					ft_lstadd_front.c	\
					ft_lstclear.c		\
					ft_lstdelone.c		\
					ft_lstiter.c		\
					ft_lstlast.c		\
					ft_lstmap.c			\
					ft_lstnew.c			\
					ft_lstsize.c

EXTRA_SOURCES	=	ft_atoll.c		\
					ft_csplit.c		\
					ft_isllong.c		\
					ft_pputchar_fd.c		\
					ft_pputstr_fd.c		\
					ft_pstrdup.c		\
					ft_putnbr_base_fd.c		\
					ft_sort_strstr_tab.c		\
					ft_stowcdup.c		\
					ft_stowcedup.c		\
					ft_stowcndup.c		\
					ft_strcasecmp.c			\
					ft_strcmp.c			\
					ft_strcchr.c			\
					ft_strcncpy.c			\
					ft_strdupchr.c			\
					ft_strduprchr.c			\
					ft_strduprnchr.c		\
					ft_strfjoin.c		\
					ft_strstrdup.c			\
					ft_strstrlen.c			\
					ft_strracat.c			\
					ft_wcscmp.c			\
					ft_wcsdup.c			\
					ft_wcslen.c			\
					ft_wcsndup.c		\
					ft_isnumeric.c		\
					ft_isspace.c		\
					ft_altoi.c			\
					ft_merge_sort.c		\
					ft_min.c			\
					ft_max.c			\
					ft_abs.c			\
					get_next_line.c		\
					skip_spaces.c

OBJECTS			=	${SOURCES:.c=.o}

BONUS_OBJECTS	=	${BONUS_SOURCES:.c=.o}

EXTRA_OBJECTS	=	${EXTRA_SOURCES:.c=.o}

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

AR				=	ar

ARFLAGS			=	rcs

all	: ${NAME}

${NAME}	: ${OBJECTS}
	${AR} ${ARFLAGS} $@ $^

bonus	: ${OBJECTS} ${BONUS_OBJECTS}
	${AR} ${ARFLAGS} ${NAME} $^

extra	: ${OBJECTS} ${BONUS_OBJECTS} ${EXTRA_OBJECTS}
	${AR} ${ARFLAGS} ${NAME} $^

c.o.	:
	${CC} ${CFLAGS} -c $< -o $(<:.c=.o)

clean	:
	rm -f ${OBJECTS} ${BONUS_OBJECTS} ${EXTRA_OBJECTS}

fclean	: clean
	rm -f ${NAME}

re	: fclean all
