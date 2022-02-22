/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:12:30 by student           #+#    #+#             */
/*   Updated: 2021/05/03 18:12:33 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>

# define TERM_NAME      "xterm-256color"
# define CMD_PROMPT		"minishell$ "
# define HIST_FILE		"/.bash_history"
# define BUFFER_SIZE	2000
# define TERM_POS		"\033[6n"

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_hist
{
	struct s_hist	*previous;
	char			*value;
	struct s_hist	*next;
}				t_hist;

typedef struct s_cmds
{
	struct s_cmds		*prev;
	char				*cmd;
	char				**str;
	int					pipe_in;
	int					pipe_out;
	char				flag;
	struct s_cmds		*next;
}	t_cmds;

typedef struct s_list_cmd
{
	char				**str;
	char				flag;
	struct s_list_cmd	*next;
}						t_list_cmd;

typedef struct s_info
{
	int					classic_in;
	int					classic_out;
	t_cmds				*cmd;
	t_cmds				*tmp_cmd;
	char				**str;
	int					input;
	int					output;
	int					error_num;
	int					pipe_fd[2];
	pid_t				pid;
	pid_t				n_fork;
	struct s_info		*next;
}						t_info;

typedef struct s_param
{
	pid_t				pid;
	int					t_pos;
	int					t_start;
	int					p_pos;
	int					res;
	int					argc;
	int					tmp_argc;
	int					tmp_argc_fl;
	int					exit_status;
	char				**argv;
	char				**envp;
	t_env				*env;
	t_hist				*hist;
	int					hist_fl;
	char				cline[BUFFER_SIZE];
	char				str[BUFFER_SIZE];
	char				*str2;
	char				command[BUFFER_SIZE];
	char				prm_name[BUFFER_SIZE];
	char				*prm_res;
	char				argv0[BUFFER_SIZE];
	struct termios		term;
	int					sq;
	int					dq;
	struct s_cmds		*lcmds;
}							t_param;

int		ft_read_bash_hist2(t_param *prms, char *tmp_hist, int i, int *y);
int		ft_read_bash_hist3(int res, int fd, char *hist, int *i);
int		ft_read_bash_hist4(char *hist, int fd);

void	ft_putstr_fd(char *s, int fd);
int		ft_putchar(int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

char	*ft_substr(char const *s, int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int		ft_isalpha(int c);
char	**ft_split(char const *s, char c);

void	ft_init_prms(t_param *prms);
int		ft_init_env(t_param *prms, char const **envp);
void	ft_copy_history(t_param *prms);
int		ft_add_last_hist(t_param *prms, char *tmp_hist);
void	ft_print_prompt(t_param *prms);

void	ft_term_redaktor(t_param *prms);
void	ft_check_keys(t_param *prms);
void	ft_key_up(t_param *prms);
void	ft_key_down(t_param *prms);
void	ft_key_right(t_param *prms);
void	ft_key_left(t_param *prms);
void	ft_key_enter(t_param *prms);
void	ft_key_other(t_param *prms);
void	ft_key_backspace(t_param *prms);
void	ft_key_delete(t_param *prms);
void	ft_key_end(t_param *prms);
void	ft_key_printable(t_param *prms);

void	ft_erase_str(char *str);
void	ft_parse_str(t_param *prms, int i);
int		ft_parse_str2(t_param *prms, int *i);
int		ft_var_name(t_param *prms, int i, int n);
void	ft_add_char_to_cmd(t_param *prms, char chr);
void	ft_add_new_to_list(t_param *prms, char chr1, char chr2);
void	ft_search_env(t_param *prms, char *str);
void	ft_search_cmd(t_param *prms, t_cmds *cmd, int i);

void	ft_copy_str(t_param *prms, char *str);
int		ft_find_env_param(t_param *prms, int i);
int		ft_isspace(int c);
void	ft_exec_cmd(t_param *prms);
void	ft_exec_cmd1(t_info *info, t_param *prms);
void	ft_exec_cmd2(t_param *prms, t_cmds *cmd);
int		ft_pipes(t_param *prms);
int		ft_own_func(t_param *prms, char **argv, t_cmds *cmd);

//included functions
int		del_from_env(char ***env, char *key);
char	*ft_get_value(char *var);
char	*ft_get_key(char *var);
int		size_env(char **env);
int		replace_value_env(char **env, char *key, char *value);
char	*find_var_env(char **env, char *key);
char	**copy_env(char **env);
char	*ft_getenv(char **env, char *key);
int		ft_setenv(char ***env, char *var);
int		add_to_env(char ***env, char *var);
int		is_our_ft(char *cmd);

void	*free_splitline(char **array);
void	ft_free_lcmds(t_param *prms);

//own functions for replace
int		ft_pwd(void);
int		ft_export(char ***env, char **argv, t_param *prms);
int		ft_unset(char ***env, char **argv, t_param *prms);
int		ft_echo(char *str, char **argv);
int		ft_env(char **env);
int		ft_cd(char *str, char ***env, t_param *prms);
int		ft_exit(t_param *prms, char **argv);

int		selector_redir(t_info *info, t_cmds *cmd, t_param *prms);
void	redir_handler(t_info *info, t_param *prms);
int		back_redir_handler(t_info *info);

//need to rewrite output to fd = 2
void	sig_choise(t_param *prms, int num);
void	sig_handler(int sig);
void	term_init2(t_param prms);
void	term_init3(t_param prms);

int		print_exp(char ***env);
int		concat_to_env(char ***env, char *var);
void	ft_split_cmd(t_info *info, t_param *prms);

int		g_sig;
#endif
