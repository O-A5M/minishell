#include "../minishell.h"

void    add_var_list();
void    replace_var();
int     ft_strncmp();

void	ft_lstdelone(t_export *lst)
{
	free(lst);
}

void	ft_lstclear(t_export **lst)
{
	t_export	*current;
	t_export	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		ft_lstdelone(current);
		current = next;
	}
	*lst = NULL;
}
t_export	*ft_new_node(char *s, char *str)
{
	t_export	*ret;

	ret = malloc(sizeof(t_export));
	if (!ret)
		return (NULL);
	ret->name = s;
	ret->value = str;
	ret->next = NULL;
	return (ret);
}

void	add_last(t_export **s, t_export *t)
{
	t_export	*tmp;

	if (!s || !t)
		return ;
	if (!*s)
	{
		(*s) = t;
	}
	else
	{
		tmp = *s;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = t;
	}
}


void	fill_the_stack(t_export **env_var)
{
	int			i;
	static char		*var_name[] = {"COLORTERM", "DBUS_SESSION_BUS_ADDRESS", "DESKTOP_SESSION", "DISPLAY", "GCC_COLORS", "GDMSESSION", "GDM_LANG", "GNOME_DESKTOP_SESSION_ID",
		"GNOME_SETUP_DISPLAY", "GNOME_TERMINAL_SCREEN", "GNOME_TERMINAL_SERVICE", "GTK_MODULES", "HOME", "IM_CONFIG_PHASE", "LANG", "LANGUAGE",
		"LOGNAME", "LS_COLORS", "OLDPWD", "PATH", "PWD", "QT_ACCESSIBILITY", "QT_IM_MODULE", "SESSION_MANAGER", "SHELL", "SHLVL", "SSH_AGENT_LAUNCHER",
		"SSH_AUTH_SOCK", "SYSTEMD_EXEC_PID", "TERM", "USER", "USERNAME", "VTE_VERSION", "WAYLAND_DISPLAY", "XAUTHORITY", "XDG_CURRENT_DESKTOP",
		"XDG_DATA_DIRS", "XDG_MENU_PREFIX", "XDG_RUNTIME_DIR", "XDG_SESSION_CLASS", "XDG_SESSION_DESKTOP", "XDG_SESSION_TYPE", "XMODIFIERS", NULL};

	i = 0;
	while (var_name[i])
	{
		add_last(env_var, ft_new_node(var_name[i], getenv(var_name[i])));
		i++;
	}
}

void    add_var_list(char *name, char *value, t_export **list)
{
    add_last(list, ft_new_node(name, value));
}

void    replace_var(char *name, char *value, t_export **list)
{
    t_export    *tmp;

    tmp = *list;
    while (ft_strncmp())
    {
        tmp = tmp->next;
    }
    ft_bzero(tmp->value, sizeof(tmp->value));
    ft_strncpy(tmp->value, value, sizeof(value));
}

void	export(char *var)
{
	t_export	*env_var;
    t_export    *tmp;

	env_var = NULL;
	fill_the_stack(&env_var);
	if (!var)
	{
        tmp = env_var;
		while (tmp)
		{
			printf("%s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
    else if()
    {
        if (ft_strncmp())
            add_var_list();
        else
            replace_var();
    }
    ft_lstclear(&env_var);
}

int	main(void)
{
	export(NULL);
}
