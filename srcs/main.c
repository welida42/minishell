/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 13:06:35 by student           #+#    #+#             */
/*   Updated: 2021/05/06 13:06:49 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	term_init2(t_param prms)
{
	tcgetattr(0, &prms.term);
	prms.term.c_lflag &= ~(ECHO);
	prms.term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &prms.term);
	tgetent(0, TERM_NAME);
}

void	term_init3(t_param prms)
{
	tcgetattr(0, &prms.term);
	prms.term.c_lflag |= (ECHO);
	prms.term.c_lflag |= (ICANON);
	tcsetattr(0, TCSANOW, &prms.term);
	tgetent(0, TERM_NAME);
}

int	ft_inc_shlvl(t_param *prms)
{
	char	*key;
	char	*value;
	char	*var;
	int		shlvl;

	if (prms->envp == NULL)
		return (1);
	var = find_var_env(prms->envp, "SHLVL");
	if (var)
	{
		key = ft_get_key(var);
		value = ft_get_value(var);
		shlvl = ft_atoi(value) + 1;
		free(value);
		value = ft_itoa(shlvl);
		replace_value_env(prms->envp, key, value);
		free(value);
		free(key);
	}
	else
		ft_setenv(&prms->envp, "SHLVL=2");
	return (0);
}

int	main(int argc, char const **argv, char **envp)
{
	t_param		prms;

	(void)argc;
	(void)argv;
	tcgetattr(0, &prms.term);
	prms.term.c_lflag &= ~(ECHO);
	prms.term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &prms.term);
	tgetent(0, TERM_NAME);
	ft_init_prms(&prms);
	prms.envp = copy_env(envp);
	ft_inc_shlvl(&prms);
	ft_copy_history(&prms);
	ft_print_prompt(&prms);
	tputs(save_cursor, 1, ft_putchar);
	sig_choise(&prms, 1);
	ft_term_redaktor(&prms);
	write(1, "\n", 1);
	return (0);
}
