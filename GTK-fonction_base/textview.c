#include <gtk/gtk.h>



typedef struct
{
  char background[26];
  char foreground[26];
  int left_margin;
  char style[26];///italic,oblique,normal
  char weight[26];///normal,gras,light,ultrabold
  int size;

}formatTv;

typedef struct
{
   GtkTextBuffer *buffer; /// le buffer associé au textview.
   GtkTextIter iter; /// l'itération au niveau du buffer.
   char text[100];
   formatTv t;

}TextView;


TextView* init_format_textbuf(TextView *txt)
{
  

  txt=(TextView*)malloc(sizeof(TextView));

  strcpy(txt->t.background,"black");
  strcpy(txt->t.foreground,"red");
  strcpy(txt->t.style,"bold");
  strcpy(txt->t.weight,"gras");
  strcpy(txt->text,"Bonjour tout le monde");
  txt->t.size=30;
  txt->t.left_margin=30;

  return((TextView*)txt);

}

GtkWidget *create_textView(TextView *view)
{
     GtkWidget *tv;
     tv = gtk_text_view_new();
     view->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
  
  ///***margin***background***foreground///
  gtk_text_buffer_create_tag(view->buffer, "lmarg", "left_margin", view->t.left_margin, NULL);
  gtk_text_buffer_create_tag(view->buffer, "foreground", "foreground", view->t.foreground, NULL); 
  gtk_text_buffer_create_tag(view->buffer, "background", "background", view->t.background, NULL); 
 
   ///*********choix du style*******
   if(!strcmp(view->t.style,"italic"))
       gtk_text_buffer_create_tag(view->buffer,"style","style",PANGO_STYLE_ITALIC,NULL);
   if(!strcmp(view->t.style,"oblique"))
      gtk_text_buffer_create_tag(view->buffer,"style","style",PANGO_STYLE_OBLIQUE,NULL);
   if(!strcmp(view->t.style,"normal"))
      gtk_text_buffer_create_tag(view->buffer,"style","style",PANGO_STYLE_NORMAL,NULL);

  ///*********choix du weight*******
   if(!strcmp(view->t.weight,"gras"))
       gtk_text_buffer_create_tag(view->buffer,"weight","weight",PANGO_WEIGHT_BOLD,NULL);
   if(!strcmp(view->t.weight,"light"))
      gtk_text_buffer_create_tag(view->buffer,"weight","weight",PANGO_WEIGHT_LIGHT,NULL);
   if(!strcmp(view->t.weight,"normal"))
      gtk_text_buffer_create_tag(view->buffer,"weight","weight",PANGO_WEIGHT_NORMAL,NULL);
   if(!strcmp(view->t.weight,"ultrabold"))
       gtk_text_buffer_create_tag(view->buffer,"weight","weight",PANGO_WEIGHT_ULTRABOLD,NULL);

  ///**size**///
  gtk_text_buffer_create_tag(view->buffer,"size","size",view->t.size,NULL);

  gtk_text_buffer_get_iter_at_offset(view->buffer, &view->iter, 0);
  gtk_text_buffer_insert_with_tags_by_name(view->buffer,&view->iter,view->text,-1,"background", "foreground","weight","style","size",NULL);
   
 
 return((GtkWidget*)tv);

}


int main(int argc, char* argv[])
{
    GtkWidget* window;
    GtkWidget *box;
 
     
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 200);

    box=gtk_box_new(FALSE,5);

    //main
    TextView *txtdecorated;

    txtdecorated = init_format_textbuf(txtdecorated);

    GtkWidget *tv = create_textView(txtdecorated);

    gtk_box_pack_start(GTK_BOX(box), tv, FALSE, FALSE, 5);

    gtk_container_add(GTK_CONTAINER(window),box);
    gtk_widget_show_all(window);
    gtk_main();
     
    return 0;
}


