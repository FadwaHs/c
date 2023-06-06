
#include <gtk/gtk.h>

typedef struct
{

  GtkWidget*parent; /*pointeur sur le parent de la fenêtre avec défilement*/
  GtkWidget*child; /*pointeur sur le fils de la fenêtre avec défilement*/

}scrolledwinProp;


scrolledwinProp * init_scrol(GtkWidget*parent,GtkWidget*child)
{
	scrolledwinProp *scrolbar;
	//allocation de la memoire pour l element

    scrolbar=(scrolledwinProp*)malloc(sizeof(scrolledwinProp));

    scrolbar->parent =parent;
    scrolbar->child = child;

    return((scrolledwinProp*)scrolbar);

}
  
void PutInContainerWithScrollBar(GtkWidget*parent,GtkWidget*child)
{

    GtkWidget*window= gtk_scrolled_window_new(NULL, NULL);
    //l'ajout du child au conteneur avec barre de défilement  
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(window),child);
    //l’ajout du child au widget parent 
    gtk_container_add(GTK_CONTAINER(parent),window);

     gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);

}

int main(int argc, char* argv[])
{
    GtkWidget* windowparent;
    GtkWidget *box;
     GtkWidget *pVBox;
         GtkWidget *pEntry;
    GtkWidget *pButton;
    GtkWidget *pLabel;
 
 
     
    gtk_init(&argc, &argv);

    windowparent = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    box = gtk_fixed_new();

     //*******//
     scrolledwinProp *scrollbar;

     scrollbar = init_scrol(windowparent,box);
     PutInContainerWithScrollBar(scrollbar->parent,scrollbar->child);

   
     gtk_container_add(GTK_CONTAINER(windowparent), box);


    pEntry = gtk_entry_new();
    
    /* Mode mot de passe */
    gtk_entry_set_visibility(GTK_ENTRY(pEntry), FALSE);
    
    /* Insertion du GtkEntry dans la GtkVBox */
    gtk_box_pack_start(GTK_BOX(box), pEntry, TRUE, FALSE, 0);

    gtk_fixed_put(GTK_FIXED(box),pEntry,10,10);
   



    gtk_widget_show_all(windowparent);

    gtk_main();
     
    return 0;
}


//add scrolbar
//*******//
scrolledwinProp *scrollbar;
scrollbar = init_scrol(F->window,fix->fix.elem);
PutInContainerWithScrollBar(scrollbar->parent,scrollbar->child);


 
