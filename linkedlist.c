#include "linkedlist.h" 
#include "mem.h"   
#include "header.h" 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Definicao da Estrutura da Lista Ligada */
struct 
ll_node
{
	void *data;
	void *next;
};

struct 
ll 
{
	size_t size; 
	p_list_node head;                   
   ptr_compare cmp;
	ptr_remove rem;
};

/* Inicia a lista ligada recebendo como argumentos um apontador para uma lista, 
	uma função para comparar dados, e uma função para remover dados, ambas 
	especificadas pelo utilizador do código 											 */
int ll_init( p_list *l, ptr_compare cmp, ptr_remove rem )
{  
	p_list new; 
	
	*l = mem_new(list);
	new = *l;
	
	new->head = NULL;
	new->size = 0;
   new->cmp  = cmp;
  	new->rem  = rem;
		
	return 1;
}

/* Insere um novo nodo à cabeça da lista, recebendo como argumentos um apontador 
	para uma lista, e os dados para 											  				*/
int ll_add_head( p_list l, void *data )
{
	p_list_node new;  
	
	assert( l );
	assert( data );
	
	if( !(new = mem_new(list_node)) )
  		return 0;
	
	new->data = data; 
	
	if( l->head ) new->next = (p_list_node)l->head;
	else			  new->next = NULL;
		
	l->head = new;
	l->size+=1;
	
	return 1;
} 

/* Função de procura da lista ligada, recebendo como argumentos um apontador
	para uma lista, e os dados para procurar										  */
void *ll_search( p_list l, void *data )
{
	p_list_node curr;
	void *data_aux = NULL;	
	
	assert( l );
	
	if( l )
	{
		for( curr=l->head; curr; curr=(list_node*)curr->next )
		{       
			if(l->cmp(curr->data,data) == 0)
			{
				data_aux = curr->data;
				break; 
			}                         
		}
	}	
  
	return data_aux;
}  

/*	Remove um nodo com dados especificos numa lista passada por argumento	*/
int ll_rem_node( p_list l, void *data )
{   
	int i;
	list_node *curr = NULL;
	
	assert( l );
	curr = l->head;
	
	for( i=0; i < (int)l->size; i++ ) 
	{  
	   if(l->cmp(curr->data,data) == 0)
		{	
			l->head = (p_list_node)curr->next;
			l->rem(curr->data); 
			l->size-=1;
			free(curr);
			return 1;
      }                  
		curr = (p_list_node)curr->next;
	}  
	return 0;
}

/* Varre uma Lista Ligada e realiza uma acção segundo a função passada
   por argumento 																	  */
int ll_traverse( p_list l, ptr_action p_action )
{  
	p_list_node curr = l->head;
	
	if(!l) return 0;
	
	while( curr )
	{                 
		p_action(curr->data);  
	   curr = (p_list_node)curr->next;
	}  
	   
	return 1;
} 

int ll_get_head( p_list l , p_list_node *node )  
{  
	if(l)
	{
	 	*node = l->head;
  		return 1;
	}
  	return 0;
}        

void ll_get_data( p_list_node n , void **data )
{
	*data = n->data;
}  

void ll_get_next( p_list_node *n )
{
	*n = ((p_list_node)n)->next;
}
 

/*	Devolve o tamanho de uma Lista Ligada passada por argumento */
int ll_get_size( p_list l )
{
	return (int)l->size;
}

/* Destrói uma Lista Ligada passada por argumento */ 
int ll_destroy( p_list l ) 
{   
	int i;
	p_list_node curr_node, last_node; 
	
	assert( l );
	
   curr_node = l->head; 
 	if(curr_node) 
	{  
		for( i=0; i < ll_get_size(l); i++ )
		{ 
			last_node = curr_node;
		   curr_node = (p_list_node)curr_node->next;   
		 	l->rem(last_node->data);
	      free(last_node);
		}
	}                     
	return 1;
}