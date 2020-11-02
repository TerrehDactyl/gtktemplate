#include <gtk/gtk.h>

/* need to make entry functions, file chooser functions, radio button functions, menu functions, 
*/

#define arraysize(x)  (sizeof(x) / sizeof((x)[0]))

void show_and_destroy( GtkWidget *window)
{
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window); //shows all widgets 
	gtk_main();//gtk main, this is the main loop of GTK
}

void button_connect_callback(GtkWidget *button, void *button_callback, gpointer data) 
{
	g_signal_connect(button, "clicked", G_CALLBACK(button_callback), data);
}


GtkWidget *create_text_display(GtkWidget *display, gboolean i, int length, int width)
{
	display = gtk_text_view_new(); //sets the display widget as a text display 

	if (i == TRUE)
	{
	gtk_text_view_set_editable (GTK_TEXT_VIEW(display),FALSE);
	}

	gtk_widget_set_size_request(display, length, width); //sets the size of the display 
	return display;
}

GtkWidget *create_frame_with_pagehead(GtkWidget *notebook, gchar *pageheads[], int i)
{
	GtkWidget *frame = gtk_frame_new (pageheads[i]);                                       
	GtkWidget *pagelabel = gtk_label_new(pageheads[i]);							
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);                  
	gtk_widget_set_size_request (frame, 100, 75);                                
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, pagelabel); 
	return frame;
}

void set_spacing(GtkWidget *widget, int colspace, int rowspace) 
{
	gtk_grid_set_column_spacing(GTK_GRID(widget), colspace);
	gtk_grid_set_row_spacing(GTK_GRID(widget), rowspace);
}

GtkWidget *createwindow(char * title, GtkWindowPosition position) 
{
	GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creates toplevel window
	gtk_window_set_title(GTK_WINDOW(widget), title); //sets a window title 
	gtk_window_set_position(GTK_WINDOW(widget), position); //opens the window in the center of the screen
	gtk_container_set_border_width(GTK_CONTAINER(widget), 5); //sets the border size of the window
	return widget;
}

GtkWidget *createnotebook(GtkWidget *window)
{
	GtkWidget *table = gtk_grid_new ();
	GtkWidget *notebook = gtk_notebook_new ();
	gtk_grid_attach(GTK_GRID(table), notebook, 0, 1, 1, 1); 
	gtk_container_add (GTK_CONTAINER (window), table);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
	return notebook;
}

void create_entries(int entry_len, GtkWidget *entries[], GtkWidget *entrygrid) 
{
	for(int i = 0; i < entry_len; i++)
	{
	entries[i]= gtk_entry_new();
	gtk_grid_attach(GTK_GRID(entrygrid), entries[i], 0, i, 1, 1); //sets the defaults for creating each table button
	}
	set_spacing(entrygrid, 4, 4);
}

GtkComboBox *create_combobox(gchar *combo_labels[], size_t combo_size, void *callback) 
{
	GtkComboBox *widget = GTK_COMBO_BOX(gtk_combo_box_text_new ());

	for (int i = 0; i < combo_size; i++)
	{
		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (widget), combo_labels[i]);
	}
	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), 0);
	g_signal_connect (widget,"changed",G_CALLBACK (callback),NULL);
	return widget;
}

GtkWidget *createlabels(gchar *labeltext[], size_t arraylen) 
{
	GtkWidget *grid = gtk_grid_new();

	for (int i=0; i<arraylen; i++)
	{
		for(int j = 0; j<1; j++)
		{	
			GtkWidget *label = gtk_label_new(labeltext[i]);
			gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1); //sets the defaults for creating each table button
		}
	}
	return grid;
}

GtkWidget *createsinglesizegrid(gchar *labels[], void *callback[], int rows, int columns)  
{
	GtkWidget *grid = gtk_grid_new(); 
	int pos = 0;

	for (int i=0; i < rows; i++) //for loop for the rows
	{
		for (int j=0; j < columns; j++) //for loop for the columns
		{
		GtkWidget *button = gtk_button_new_with_label(labels[pos]); //sets each button label to the respective button 
		button_connect_callback(button, callback[pos],NULL); //attaches the button to the respective callback
		gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1); //sets the defaults for creating each table button
		gtk_widget_set_size_request(button, 70, 30); //sets the size of the buttons
		pos++; //changes the position 
		}
		set_spacing(grid, 4, 4);
	}
	return grid;
}

void get_entry_text(GtkWidget *widget[], const gchar *entries[], size_t entrysize) //need to work on this 
{
	for(int i = 0; i < entrysize; i++)
	{
		entries[i] = gtk_entry_get_text(GTK_ENTRY(widget[i]));
	}
}

GtkWidget *create_checkbox(GtkWidget *window, const gchar *label, gboolean status, void *callback, GtkWidget *box)
{
	GtkWidget *checkbutton = gtk_check_button_new_with_label (label);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton), status);
	g_signal_connect (GTK_TOGGLE_BUTTON (checkbutton), "toggled", G_CALLBACK (callback), window);
	//gtk_container_add (GTK_CONTAINER (box), checkbutton);
	return checkbutton;
}

void add_context(const gchar *style, GtkWidget *widget) //should already be modular 
{
	GtkCssProvider* Provider = gtk_css_provider_new();
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "Styles.css", NULL);
	gtk_style_context_add_class(context, style);
	gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}