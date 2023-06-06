

#include <gtk/gtk.h>


typedef struct FrameProp
{

gchar* label; // label de frame
int Hauteur; //la hauteur de frame
int Largeur; // la largeur de frame

}FrameProp;



GtkWidget*CreatFrame(FrameProp prop)
{

   GtkWidget*frame = gtk_frame_new(prop.label);

   if(prop.Hauteur>0 && prop.Largeur>0)

   gtk_widget_set_size_request(frame,prop.Hauteur, prop.Largeur);

   return((GtkWidget*)frame);

}//fin de la fonction CreatFrame.






#include <stdlib.h>
#include <gtk/gtk.h>
 
int main(int argc, char **argv)
{
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pFrame;
     GtkWidget *pFrame2;
 
    gtk_init(&argc, &argv);
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    /* On ajoute un espace de 5 sur les bords de la fenêtre */
    gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Gtkframe");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
   
 
    pVBox =  gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
   
    /* creation des frames with macros */

     FrameProp frame;
     frame.label = "Etat civil";
     frame.Hauteur =50;
     frame.Largeur=70;


     FrameProp frame2;
     frame2.label = "Etat civil2";
     frame2.Hauteur =50;
     frame2.Largeur=70;

    pFrame =CreatFrame(frame);
    pFrame2 =CreatFrame(frame2);

    /******/
     
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame2, TRUE, FALSE, 0);
 
    gtk_widget_show_all(pWindow);
    gtk_main();
 
    return EXIT_SUCCESS;
}
