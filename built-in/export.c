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

//The main function.
void	export(char *var, t_export *env)
{
    t_export    *tmp;
    char        **new_var;

    //cheking if the there is no argument so I only display the variables.
	if (!var)
	{
        tmp = env;
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
		add_last(&env, ft_new_node(new_var[0], new_var[1]));
		tmp = env;
		while (tmp)
		{
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			tmp = tmp->next;
		}
    }
}
