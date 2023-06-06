

#include <gtk/gtk.h>



void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
    /* Arret de la boucle évènementielle */
    gtk_main_quit();
}

 
int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    GtkWidget*  window;
  
    GtkWidget *pButton[4];
    
 

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //window function
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW (window), "Les GtkBox");
    gtk_window_set_default_size (GTK_WINDOW (window), 300, 300);
    

    
    /* Connexion du signal "destroy" */
    g_signal_connect(G_OBJECT(window), "destroy",     G_CALLBACK(OnDestroy), NULL);
   
 
    /* Creation des boutons */
    pButton[0] = gtk_button_new_with_label("Bouton 1");
    pButton[1] = gtk_button_new_with_mnemonic("Bouton quiter");
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(OnDestroy), NULL);
    pButton[2] = gtk_button_new_with_label("Bouton 3");
    pButton[3] = gtk_button_new_with_label("Bouton 4");
  
     /* Création de la GtkBox verticale */
     GtkWidget *box= gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
     /* Ajout de la GtkVBox dans la fenêtre */
     gtk_container_add(GTK_CONTAINER(window),box);
     
     
      /* Ajout de Bouton 1 dans la GtkVBox */
      gtk_box_pack_start(GTK_BOX(box),pButton[0], TRUE, FALSE, 0);
    
      /* Création de la box horizontale */
      GtkWidget *boxh= gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
      
      /* Ajout de la GtkHBox dans la GtkVBox */
      gtk_box_pack_start(GTK_BOX(box),boxh, TRUE, TRUE, 0);
      
       /* Ajout des boutons 2 et 3 dans la GtkHBox */
       gtk_box_pack_start(GTK_BOX(boxh), pButton[1], TRUE, TRUE, 0);
       gtk_box_pack_start(GTK_BOX(boxh), pButton[2], TRUE, TRUE, 0);
       
       /* Ajout du dernier bouton dans la GtkVBox */
      gtk_box_pack_start(GTK_BOX(box), pButton[3], TRUE, FALSE, 0);
      
      
      
      //FOnction BOX : 
      
      ///homogeneous : TRUE si l'on veut que box soit homogène, FALSE sinon.
      gtk_box_set_homogeneous(GTK_BOX(box), FALSE);
      
      //Utilisée pour définir l'espacement entre les widgets.
      gtk_box_set_spacing(GTK_BOX(box),0);
     
  
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}







