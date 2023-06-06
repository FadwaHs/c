#include <gtk/gtk.h>
#include <cairo.h>

static int width, height,
           posX = 0,
           vX = 2;


           
static gboolean move(GtkWidget* widget)
{
    GtkWidget* window = gtk_widget_get_toplevel(widget);
    gtk_window_get_size(GTK_WINDOW(window), &width, &height);

    if(posX + vX >= width || posX + vX == 0)
        vX = -vX;
    posX += vX;

    gtk_widget_queue_draw(widget);
    return TRUE;
}

static gboolean draw(GtkWidget* widget, cairo_t* cr)
{
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 100);

    cairo_rectangle(cr, posX + 0.9, height/2 + 0.5, 100, 100);
    cairo_stroke(cr);

    return FALSE;
}

int main(int argc, char** argv)
{
    GtkWidget* window;
    GtkWidget* darea;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    darea = gtk_drawing_area_new();

    gtk_container_add(GTK_CONTAINER(window), darea);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(draw), NULL);

    g_timeout_add(16, (GSourceFunc)move, window);

    gtk_widget_show_all(window);
    gtk_main();
}
  

  