
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct
{

   GtkWidget *dialog; ///widget d'une entrée.
   GtkWindow *parent;
   GtkDialogFlags flags;
   GtkMessageType type;
   GtkButtonsType buttons;
   gchar *message_format;
   gchar *secondrytext;
}Dialog;




Dialog* init_dialog(GtkWindow *parent,GtkDialogFlags flags, GtkMessageType type,GtkButtonsType buttons,gchar * message_format,gchar *secondrytext)
{
   Dialog * mondialog = NULL;

  //allocation mémoire :
  mondialog = (Dialog*)malloc (sizeof (Dialog)); 
  mondialog->message_format = (gchar*)malloc (30*sizeof (gchar));
  mondialog->secondrytext = (gchar*)malloc (30*sizeof (gchar));


   mondialog->parent = parent;
   mondialog->flags = flags;
   mondialog->type=type;
   mondialog->buttons=buttons;
   strcpy (mondialog->message_format, message_format);
   strcpy (mondialog->secondrytext, secondrytext);


   return((Dialog*)mondialog);

}

void create_dialog(Dialog * mondialog)
{
   GtkWidget * hello=NULL;
   hello = gtk_message_dialog_new (mondialog->parent, mondialog->flags, mondialog->type, mondialog->buttons,mondialog->message_format);
   gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (hello), mondialog->secondrytext);

   gtk_dialog_run(GTK_DIALOG (hello)); 
}

int main (int argc, char *argv[]) {

    gtk_init (&argc, &argv);

    GtkWidget*window;
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

    Dialog * mondialog;
    mondialog = init_dialog(window, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "Voulez Vous afficher Une image","");
    create_dialog(mondialog);
   
        return 0;
}




