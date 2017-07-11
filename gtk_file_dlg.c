#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

static void destroy(GtkWidget *window, gpointer data)
{
    gtk_main_quit();
}

GtkWidget* window;





static void cb_button(GtkButton* button, gpointer data)
{
    
    printf("hello\n");

    GtkWidget *dlg;
    GtkWidget *parent;

    GtkFileChooserAction action[] = {GTK_FILE_CHOOSER_ACTION_OPEN ,
                                     GTK_FILE_CHOOSER_ACTION_SAVE ,
                                     GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER ,
                                     GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER
    };


    parent = GTK_WIDGET(g_object_get_data(G_OBJECT(data), "parent"));

    dlg = gtk_file_chooser_dialog_new("File Chooser Dialog",
                                      //GTK_WINDOW(parent),
                                      GTK_WINDOW(window),
                                      action[0],
                                      GTK_STOCK_CANCEL,
                                      GTK_RESPONSE_CANCEL,
                                      GTK_STOCK_OPEN,
                                      GTK_RESPONSE_ACCEPT,
                                      NULL
                                      );




    gint response;
    gchar *filename;
    gchar *folder;

    GtkEntry *entry;
    entry = GTK_ENTRY(data);

    GtkFileFilter *filter;
    filter = gtk_file_filter_new ();
    gtk_file_filter_set_name(filter, "ALL Files(*.*)");
    gtk_file_filter_add_pattern(filter, "*");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dlg) , filter);


    filter = gtk_file_filter_new ();
    gtk_file_filter_set_name(filter, "Text Files(*.txt)");
    gtk_file_filter_add_pattern(filter, "*.txt");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dlg) , filter);

    //g_signal_connect(dlg, "notify::filter", G_CALLBACK(filter_changed), NULL);


    gtk_widget_show_all(dlg);

    response = gtk_dialog_run(GTK_DIALOG(dlg));

    if (response == GTK_RESPONSE_ACCEPT) {
        filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dlg));
        folder= gtk_file_chooser_get_current_folder (GTK_FILE_CHOOSER(dlg));
        g_print ("%s\n" , folder);
        g_free (folder);
        gtk_entry_set_text(entry, filename);
        g_free (filename);
    }
    else if (response == GTK_RESPONSE_CANCEL) {
        g_print ("Cancel button was pressed.\n");
    }
    else {
        g_print ("Another response was recieved.\n");
    }

    gtk_widget_destroy(dlg);

    


}

int main(int argc, char* argv[])
{

    //GtkWidget* window;
    GtkWidget* button;
    GtkWidget* vbox;
    GtkWidget* hbox;
    GtkWidget *entry;
    int i;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /*  ウィンドウの初期設定  */
    gtk_window_set_title(GTK_WINDOW(window), "Hello");  //  title
    gtk_widget_set_size_request(window, 200, 200);      //  window siz


    g_signal_connect(G_OBJECT(window), "destroy", 
                     G_CALLBACK(destroy), NULL);




    /* ウィンドウの境界幅を設定します */
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    vbox = gtk_vbox_new(FALSE,5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    
    hbox = gtk_hbox_new(FALSE, 5);
    

   
    entry = gtk_entry_new ();
    gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, FALSE, 0);
    g_object_set_data (G_OBJECT(entry), "parent", (gpointer)window);



    
    
    button = gtk_button_new_with_label("file select");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cb_button), (gpointer)entry);

    gtk_box_pack_start(GTK_BOX(hbox), button, FALSE, FALSE, 0);

    
    
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    
    gtk_widget_show_all(window);
    gtk_main();


    
    return 0;
}
