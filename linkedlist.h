#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define NDEBUG

/* Macro para alocacao de memoria */
#define ALLOC(type, n) (type *) malloc((n) * sizeof(type))

/* Apontadores para as funcoes compare, remove, e action(para mapear uma lista)*/
typedef int  (*ptr_compare)( void *, void * ); 
typedef int  (*ptr_remove) ( void * );	
typedef void (*ptr_action) ( void * );

/* Estrutura genérica da Lista Ligada */
typedef struct ll_node list_node, *p_list_node; 
typedef struct ll list, *p_list;   

/* Protótipos das funções de manutenção da Lista Ligada */
extern int ll_init	   ( p_list *, ptr_compare, ptr_remove);
extern int ll_add_head 	( p_list  , void * 	   );
extern void *ll_search 	( p_list  , void * 	   );
extern int ll_rem_node 	( p_list  , void *		);   
extern int ll_traverse 	( p_list  , ptr_action  );
extern int ll_destroy 	( p_list  ); 
extern int ll_get_size	( p_list  ); 
extern int ll_get_head  ( p_list  , p_list_node*); 
extern void ll_get_next ( p_list_node * );
extern void ll_get_data ( p_list_node, void ** );



#endif