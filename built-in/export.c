#include "../minishell.h"

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

//This one adds node to the end of the list.
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

//This is the function that stores the variables and their values in the stack.
void	fill_the_stack(t_export **env_var)
{
	int			i;
    //this is not efficiant I need to change this methode.
	char		*var_name[] = {"COLORTERM", "DBUS_SESSION_BUS_ADDRESS", "DESKTOP_SESSION", "DISPLAY", "GCC_COLORS", "GDMSESSION", "GDM_LANG", "GNOME_DESKTOP_SESSION_ID",
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

//The main function.
void	export(char *var)
{
	t_export	*env_var;
    t_export    *tmp;
    char        **new_var;

	env_var = NULL;
    //filling the stack with the system variables.
	fill_the_stack(&env_var);
    //cheking if the there is no argument so I only display the variables.
	if (!var)
	{
        tmp = env_var;
		while (tmp)
		{
			printf("%s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
	}
    //Checking if the input is valide then add a new variable
    //if it is valid.
    if (ft_strchr(var, '='))
    {
		//Spliting the input into two parts:
		//the variable name and value.
		new_var = ft_split(var, '=');
		//adding the variable to the list.
		add_last(&env_var, ft_new_node(new_var[0], new_var[1]));
		tmp = env_var;
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
    }
}

int	main(void)
{
	export("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=helooloooooo");
}
