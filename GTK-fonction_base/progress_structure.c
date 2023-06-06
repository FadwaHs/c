
#include <gtk/gtk.h>

typedef struct
{
GtkWidget *progress ; // le conteneur du barre de progression

gdouble fraction; // valeur de progression actuelle

gdouble eugmentation; // la valeur de l’augmentation à faire au cours de la progression

}Bar_progress;


Bar_progress* creeBar(gdouble eugmentat)

{ 
  // allocation mémoire
  Bar_progress*LaBar = (Bar_progress*)malloc(sizeof(Bar_progress));

  LaBar->eugmentation = eugmentat; // insertion de la valeur

 // initialisation du fraction
 LaBar->fraction = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (LaBar->progress));

 LaBar->progress= gtk_progress_bar_new ();

return(Bar_progress*)LaBar;

}


static gboolean augmenter_barre (Bar_progress*LaBar)
{

// augmentation du fraction
LaBar->fraction+=LaBar->eugmentation;

// actualisation de la barre
gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (LaBar->progress),

LaBar->fraction);

// si la fraction n'a encore atteindre la fin
if (LaBar->fraction < 1.0)
  return TRUE;

return FALSE;

}
 
int main(int argc,char **argv)
{
   GtkWidget* pWindow;
   GtkWidget *pMainVBox;
   GtkWidget *pButton;

 
   gtk_init(&argc,&argv);
 
   pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(pWindow), "GtkProgressBar");
   gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   gtk_container_set_border_width(GTK_CONTAINER(pWindow), 4);
 
   pMainVBox = gtk_box_new(TRUE, 0);
   gtk_container_add(GTK_CONTAINER(pWindow), pMainVBox);
 
   /* Création de la barre de progression  with macros*/

   Bar_progress* pg;
   pg =creeBar(0.1);

   gtk_box_pack_start(GTK_BOX(pMainVBox), pg->progress, TRUE, FALSE, 0);

   pButton = gtk_button_new_with_label("Ajouter 10%");
   gtk_box_pack_start(GTK_BOX(pMainVBox), pButton, TRUE, FALSE, 0);

   g_signal_connect_swapped(G_OBJECT(pButton), "clicked", G_CALLBACK(augmenter_barre), pg);

   //augmenter_barre (pg);

   gtk_widget_show_all(pWindow);
   gtk_main();
 
   return EXIT_SUCCESS;
}
