
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct {

 GtkWidget *comboBox; // notre objet
 GtkWidget *container; // le conteneur
 gchar *nom; // le nom de l'objet
 int posx;
 int posy; //la position

} ComboBoxobject;

ComboBoxobject *init_combobox(GtkWidget *pere, gchar *nom,int x,int y){

 ComboBoxobject *cb = NULL;
 cb = (ComboBoxobject*) malloc (sizeof (ComboBoxobject));
 cb->comboBox = NULL;
 cb->container = pere;
 if (nom)
 {
 cb->nom = (gchar*) malloc (35*sizeof (gchar));
 strcpy (cb->nom, nom);
 }
 else cb->nom = NULL;
 cb->posx=x;
 cb->posy=y;

 return ((ComboBoxobject*) cb);

}

ComboBoxobject *create_combobox (ComboBoxobject *cb)
{

 cb->comboBox = gtk_combo_box_text_new();
 gtk_widget_set_name (cb->comboBox, cb->nom);
 return ((ComboBoxobject*) cb);

}

void combobox_add (ComboBoxobject *cb, gchar *text){

 gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(cb->comboBox),NULL, text);
 gtk_combo_box_set_active(GTK_COMBO_BOX(cb->comboBox), 0);

}

gchar *combobox_get (ComboBoxobject *cb){

 return ((gchar*) gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(cb->comboBox)));

}

//Changer la taille d'un composant

void change_size(GtkWidget* widget, gint width, gint height)
{
     gtk_widget_set_size_request(widget,width,height);
}


int main(int argc,char** argv)

{

    gtk_init(&argc,&argv);

    
    GtkWidget*window,*box;

    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

 
    box = gtk_box_new(FALSE, 0);


    ComboBoxobject * comb;
    comb = init_combobox(box,NULL,10,10);
    comb = create_combobox(comb);
    combobox_add(comb,"fort");
    combobox_add(comb,"faible");
    combobox_add(comb,"moyenne");
    combobox_add(comb,"tres port");


    ComboBoxobject * comb2;
    comb2 = init_combobox(box,NULL,100,100);
    comb2 = create_combobox(comb2);
    combobox_add(comb2,"boutaina ");
    combobox_add(comb2,"Mip the little one ");
    combobox_add(comb2,"Merci the big one ");
    combobox_add(comb2,"Nasa pilot");

    change_size(comb->comboBox, 10, 4);

    gtk_box_pack_start(GTK_BOX(box),comb->comboBox, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box),comb2->comboBox, TRUE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;


}