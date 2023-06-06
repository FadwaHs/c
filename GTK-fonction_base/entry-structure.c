
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>


typedef struct
{

   GtkWidget *entry; ///widget d'une entrée.
   int len; ///la longueur d'entrée.
   int width; ///largeur d'entrée.
   gboolean visible; ///le texte est visible ou pas.
   gboolean editable;///on peut saisir par clavier.
  char* text_to_set;///le texte à saisir.
  char* text_to_get;///le texte à récupérer.


}Entry;



Entry* init_entry(gboolean visible,gboolean editable,int len,int width)
{
    Entry * entry =NULL;
    entry = (Entry*)malloc (sizeof (Entry)); 

     //initialisation 
      entry->visible =visible;
      entry->len=len;
      entry->width=width;
      entry->editable = editable;

      return((Entry*)entry);
}

// creation d'un GTKentry
GtkWidget *create_entry(Entry *e,GtkWidget *entry)
{


   entry=gtk_entry_new();

   gtk_widget_set_size_request(entry,e->len,e->width);

   gtk_entry_set_visibility(GTK_ENTRY(entry),e->visible);

   gtk_editable_set_editable(GTK_EDITABLE(entry),e->editable);


return (GtkWidget*)entry;
}






int main(int argc, char* argv[])
{
     GtkWidget *pWindow;
     GtkWidget *pVBox;

     GtkWidget *pEntry;

     GtkWidget *pEntry1;
    
    
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Le widget GtkEntry");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   
    pVBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 

    /* Creation du GtkEntry with macro */

       Entry *e;
       Entry *e1;

       e = init_entry(TRUE,TRUE,4,5);
       e1 = init_entry(FALSE,TRUE,4,5);
       pEntry = create_entry(e,pEntry);
       pEntry1 = create_entry(e1,pEntry1);


     
    /* Insertion du GtkEntry dans la GtkVBox */
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pEntry1, TRUE, FALSE, 0);
 
    gtk_widget_show_all(pWindow);
    gtk_main();

    return 0;
}
