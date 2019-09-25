#include <string.h>
#include "malloc.h"

int	def()
{
	t_meta *caca;
	
	my_malloc(16);
	caca = my_malloc(32);
	my_malloc(16);
	my_free(caca);
	my_malloc(16);
	print_heap_state();
	return (0);
}

int	expand()
{
	printf("size of meta:%ld or 0x%hhX\n", sizeof(t_meta), (int)sizeof(t_meta));
	printf("espace memoire 1: %p\n", extend_heap(16));
	printf("espace memoire 2: %p\n", extend_heap(16));
	return (0);
}

int	stupid()
{
	printf("espace memoire 1: %p\n", stupid_malloc(16));
	printf("espace memoire 2: %p\n", stupid_malloc(16));
	printf("Il n'y a pas moyen de definir ou commence un partie de la memoire ni ou elle finit et on ne sait pas si la memoire est utilisee ==> on ne peux pas reutiliser un espace car il est en bas du tas\n");
	return (0);
}

int	main(int argc, char **argv)
{
	printf("\e[1;36mMemory Allocation Project\e[0m\n");
	global_base = NULL;
	global_last = NULL;

	if (argc != 2)
		return (def());
	else
	{
		if (!strcmp(argv[1], "stupid"))
			return (stupid());
		if (!strcmp(argv[1], "expand_heap"))
			return (expand());
	}
	return (0);
}
