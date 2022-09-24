
#include "../../include/minishell.h"

#include "stdio.h"

void parse_test(char *test_line);

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;

	init_data(envp);

	parse_test("Hello");

	return 0;
}


void parse_test(char *test_line) {

	t_params	*params = cmd_parse(test_line);

	for (int i = 0; params->exec_arg[i]; ++i) {
		printf("%s\n", params->exec_arg[i]);
	}
	return;
}
