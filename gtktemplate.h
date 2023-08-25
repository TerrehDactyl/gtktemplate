#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <cairo.h>
/* file chooser functions, menu functions*/
#define YELLOW 848749
#define BLUE 31261
#define GREEN 159890
#define PURPLE 831441
#define RED 6580
#define ORANGE 824241
#define PINK 32907
#define WHITE 168806
#define BLACK 155902
#define TEAL 33243
#define BROWN 157105
#define GREY 31976
#define AQUA 31257
#define INDIGO 803251
#define LAVENDER 20167494
#define FOREST 796216
#define LIME 32396
#define WINE 33776
#define ZOOM_X 100.0
#define ZOOM_Y 100.0

gboolean transpose = FALSE;

typedef struct variables
{
	char *pointer[5];
	int current;
	int max;
}location;

#define arraysize(x)  (sizeof(x) / sizeof((x)[0]))

void show_and_destroy( GtkWidget *window)
{
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window); //shows all widgets 
	gtk_main();//gtk main, this is the main loop of GTK
}

void button_connect_callback(GtkWidget *button, gchar *action, void *button_callback, location *data) 
{
	g_signal_connect(button, action, G_CALLBACK(button_callback), data);
}

GtkWidget *create_text_display(gboolean i, int length, int width)
{
	GtkWidget *display = gtk_text_view_new(); //sets the display widget as a text display 

	if (i == TRUE)
	{
		gtk_text_view_set_editable (GTK_TEXT_VIEW(display),FALSE);
	}

	gtk_widget_set_size_request(display, length, width); //sets the size of the display 
	return display;
}

GtkWidget *create_frame_with_pagehead(GtkWidget *notebook, gchar pageheads[])
{
	GtkWidget *frame = gtk_frame_new (pageheads);                                       
	GtkWidget *pagelabel = gtk_label_new(pageheads);							
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

GdkPixbuf *create_pixbuf(const gchar *filename)
{
	GdkPixbuf *pixbuf;
    GError *error = NULL;
    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if(!pixbuf) 
   {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }
   return pixbuf;
}

GtkWidget *create_window(char * title, GtkWindowPosition position, const gchar *filename) 
{
	GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creates toplevel window
	gtk_window_set_title(GTK_WINDOW(widget), title); //sets a window title 
	gtk_window_set_position(GTK_WINDOW(widget), position); //opens the window in the center of the screen
    gtk_window_set_icon(GTK_WINDOW(widget), create_pixbuf(filename));
	return widget;
}

GtkWidget *create_sized_window(char * title, GtkWindowPosition position, int HEIGHT, int WIDTH, const gchar *filename) 
{
	GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creates toplevel window
	gtk_window_set_title(GTK_WINDOW(widget), title); //sets a window title 
	gtk_window_set_position(GTK_WINDOW(widget), position); //opens the window in the center of the screen
    gtk_window_set_icon(GTK_WINDOW(widget), create_pixbuf(filename));
    gtk_window_set_default_size (GTK_WINDOW (widget), WIDTH, HEIGHT);
	return widget;
}

GtkWidget *create_custom_window(char * title, GtkWindowType type, GtkWindowPosition position, const gchar *filename, int width, int height) 
{
	GtkWidget *widget = gtk_window_new(type); //creates toplevel window
	gtk_window_set_title(GTK_WINDOW(widget), title); //sets a window title 
	gtk_window_set_position(GTK_WINDOW(widget), position); //opens the window in the center of the screen
	gtk_window_set_icon(GTK_WINDOW(widget), create_pixbuf(filename));
	
	if(height && width)
		gtk_window_set_default_size ((GtkWindow *)widget, width, height);
	return widget;
}

GtkWidget *create_notebook(GtkWidget *window)
{
	GtkWidget *table = gtk_grid_new ();
	GtkWidget *notebook = gtk_notebook_new ();
	gtk_grid_attach(GTK_GRID(table), notebook, 0, 1, 1, 1); 
	gtk_container_add (GTK_CONTAINER (window), table);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
	return notebook;
}

GtkWidget *create_entries(int entry_len, GtkWidget *entries[]) //segfaults? 
{
	GtkWidget *entry_grid = gtk_grid_new();
	for(int i = 0; i < entry_len; i++)
	{
		entries[i]= gtk_entry_new();
		gtk_grid_attach(GTK_GRID(entry_grid), entries[i], 0, i, 1, 1); //sets the defaults for creating each table button
	}
	set_spacing(entry_grid, 4, 4);
	return entry_grid;
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

// GtkComboBox *create_combobox(gchar *combo_labels[], size_t combo_sizes, void *callback) 
// {
// 	GtkComboBox *widget = GTK_COMBO_BOX(gtk_combo_box_text_new ());
// 	size_t combo_size = 0;
// 	while(*combo_labels[combo_size++])
// 	{
// 		g_print("%d\n", combo_size);
// 	}
// 	for (int i = 0; i < combo_size; i++)
// 	{
// 		gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (widget), combo_labels[i]);
// 	}
// 	gtk_combo_box_set_active (GTK_COMBO_BOX (widget), 0);
// 	g_signal_connect (widget,"changed",G_CALLBACK (callback),NULL);
// 	return widget;
// }


GtkWidget *create_labels(gchar *label_text[], size_t array_len) 
{
	GtkWidget *grid = gtk_grid_new();

	for (int i=0; i<array_len; i++)
	{
		for(int j = 0; j<1; j++)
		{	
			GtkWidget *label = gtk_label_new(label_text[i]);
			gtk_grid_attach(GTK_GRID(grid), label, j, i, 1, 1); //sets the defaults for creating each table button
		}
	}
return grid;
}

GtkWidget *create_single_size_grid(gchar *labels[], void *callback[], location *data, int rows, int columns)  
{
	GtkWidget *grid = gtk_grid_new(); 
	int pos = 0;
	for (int i=0; i < rows; i++) //for loop for the rows
	{
		for (int j=0; j < columns; j++) //for loop for the columns
		{
		GtkWidget *button = gtk_button_new_with_label(labels[pos]); //sets each button label to the respective button 
		button_connect_callback(button, "clicked",callback[pos], data); //attaches the button to the respective callback
		gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1); //sets the defaults for creating each table button
		gtk_widget_set_size_request(button, 70, 30); //sets the size of the buttons
		pos++; //changes the position 
		}
	set_spacing(grid, 4, 4);
	}
return grid;
}

GtkWidget *create_two_size_grid(gchar *labels[], void  *callback[], int rows, int columns,  int norm_width, int norm_len, int spec_width, int spec_len, int range)
{
	GtkWidget *grid = gtk_grid_new();
	int pos = 0;
	for (int i=0; i < rows ; i++) //for loop for the rows
	{
		for (int j=0; j < columns; j++) //for loop for the columns
		{ 
		GtkWidget *button = gtk_button_new_with_label(labels[pos]); //sets each button label to the respective button 
		button_connect_callback(button, "clicked", callback[pos], NULL); //attaches the button to the respective callback
		gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1); //sets the defaults for creating each table button
		if (pos <= range)
			gtk_widget_set_size_request(button, spec_width, spec_len); //sets the size of the buttons
		else 
			gtk_widget_set_size_request(button, norm_width, norm_len); //sets the size of the buttons
		pos++;
		}
		set_spacing(grid, 4, 4);
	}
	return grid;
}

void get_entry_text(GtkWidget *widget[], const gchar *entries[], size_t entry_size) //need to work on this 
{
	for(int i = 0; i < entry_size; i++)
		entries[i] = gtk_entry_get_text(GTK_ENTRY(widget[i]));
}

// const gchar *get_entry_text(GtkWidget *widget[]) //need to work on this 
// {
// 	size_t entry_size = arraysize(widget);
// 	printf("%d", entry_size);
// 	const gchar *entries[entry_size];
// 	for(int i = 0; i < entry_size; i++)
// 	{
// 		entries[i] = gtk_entry_get_text(GTK_ENTRY(widget[i]));
// 	}
// 	return *entries;
// }

GtkWidget *create_checkbox(GtkWidget *window, const gchar *label, gboolean status, void *callback)
{
	GtkWidget *check_button = gtk_check_button_new_with_label (label);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check_button), status);
	g_signal_connect (GTK_TOGGLE_BUTTON (check_button), "toggled", G_CALLBACK (callback), window);
	//gtk_container_add (GTK_CONTAINER (box), check_button);
	return check_button;
}

void add_context(const gchar *style, GtkWidget *widget) //should already be modular 
{
	GtkCssProvider* Provider = gtk_css_provider_new();
	GtkStyleContext *context = gtk_widget_get_style_context(widget);
	gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "Styles.css", NULL);
	gtk_style_context_add_class(context, style);
	gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

GtkWidget *create_radio_buttons(gchar *labels[], void *callback[], int arraysize)
{
	GtkWidget *grid = gtk_grid_new();
	GtkWidget *root_button = gtk_radio_button_new_with_label(NULL, labels[0]);
	button_connect_callback(root_button,"clicked", callback[0], NULL);
	gtk_grid_attach(GTK_GRID(grid), root_button, 0, 0, 1, 1); //sets the defaults for creating each table button
	GtkWidget *label_widget;
	for (int i = 1; i<arraysize; i++)
	{
		label_widget = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(root_button), labels[i]);
		gtk_grid_attach(GTK_GRID(grid), label_widget, i, 0, 1, 1); //sets the defaults for creating each table button
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(label_widget), FALSE);
		button_connect_callback(label_widget, "clicked", callback[i], NULL);
	}
	return grid;
}

GtkWidget *create_menu(gchar *headers, gchar *menu_array[], int array_len, void *callback[])
{
	char buf[128];
	sprintf (buf, "%s", headers);
  	GtkWidget *root_menu = gtk_menu_item_new_with_label (buf);
	GtkWidget *menu;
	GtkWidget *menu_items;
	menu = gtk_menu_new();
	for(int j = 0; j<array_len; j++)
	{
		sprintf (buf, "%s", menu_array[j]);
		menu_items = gtk_menu_item_new_with_label(buf);
		button_connect_callback(menu_items,"activate", callback[j], NULL);
		gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
		gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu), menu);
	}
	return root_menu;
}

void create_file_choosers(GtkButton *button, location* data)
{
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;
	GtkWindow *new_window;
	new_window = (GtkWindow *)gtk_window_new(GTK_WINDOW_POPUP);
	GtkWidget *file_choosers = gtk_file_chooser_dialog_new ("Open File", new_window, action, ("_Cancel"), GTK_RESPONSE_CANCEL, ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
	res = gtk_dialog_run (GTK_DIALOG (file_choosers));
	if(data->current == data->max)
		data->current = 0;

	if (res == GTK_RESPONSE_ACCEPT)
	  {
	   GtkFileChooser *chooser = GTK_FILE_CHOOSER (file_choosers);
	   data->pointer[data->current] = gtk_file_chooser_get_filename (chooser);
	   data->current++;
	  }
	gtk_widget_destroy (file_choosers);
}

GtkWidget *create_progress_bar(void *callback)
{
	GtkWidget *progress_bar = gtk_progress_bar_new ();
	g_timeout_add (500, callback, GTK_PROGRESS_BAR (progress_bar));
	return progress_bar;
}

const unsigned long hash(const char *str) 
{
    unsigned long hash = 25;  
    int c;

    while ((c = *str++))
        hash = ((hash << 2) + hash) + c;
    return hash;
}

void cairo_color(cairo_t *cr, char* color)
{
    float r=0, g=0, b=0;
    switch(hash(color))
    {
    case YELLOW: r = 1, g = 1, b = 0;
        break;
    case BLUE: r = 0, g = 0, b = 1;
        break;
    case AQUA: r = 0, g = 1, b = 1;
        break;
    case INDIGO: r = 0, g = 0.11, b = 0.4;
        break;
    case FOREST: r = 0, g = 0.3, b = 0;
        break;
    case LIME: r = 0, g = 1, b = 0.2;
        break;
    case WINE: r = 0.2, g = 0, b = 0.2;
        break;
    case LAVENDER: r = 0.4, g = 0, b = 1;
        break;
    case GREEN: r = 0, g = 1, b = 0;
        break;
    case PURPLE: r = 0.5, g = 0, b = 1;
        break;
    case RED: r = 1, g = 0, b = 0;
        break;
    case ORANGE: r = 1, g = 0.5, b = 0;
        break;
    case PINK: r = 1, g = 0, b = 1;
        break;
    case WHITE: r = 1, g = 1, b = 1;
        break;
    case BLACK: r = 0, g = 0, b = 0;
        break;
    case TEAL: r = 0, g = 1, b = 0.5;
        break;
    case BROWN: r = 0.2, g = 0.1, b = 0.1;
        break;
    case GREY: r = 0.3, g = 0.3, b = 0.3;
        break;
    default:
        printf("[ERROR] '%s' is not a valid color. Options are YELLOW, BLUE, AQUA, INDIGO, FOREST, LIME, WINE, LAVENDER, GREEN, PURPLE, RED, ORANGE, PINK, WHITE, BLACK, TEAL, BROWN and GREY.\n", color);
        break;
    }
    cairo_set_source_rgb (cr, r, g, b);
}

GtkWidget *create_image_area(void *callback, gpointer image, int height, int width)
{
	GtkWidget *widget = gtk_drawing_area_new();
	if(height && width)
		gtk_widget_set_size_request(widget, width, height); //sets the size of the buttons
	
	g_signal_connect (G_OBJECT (widget), "draw", G_CALLBACK (callback), image);

	return widget;
}

void draw_image(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
	const char *data = (const char *) user_data;
	GdkPixbuf *pixbuf = create_pixbuf(data); 
	gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
	cairo_paint (cr);
}

void draw_quad_axis(cairo_t *cr, double max_x, double max_y, char *color)
{   
	cairo_color(cr, color); 
    cairo_move_to (cr, -max_x, 0.0);
    cairo_line_to (cr, max_x, 0.0);
    cairo_move_to (cr, 0.0, -max_y);
    cairo_line_to (cr, 0.0, max_y);
    cairo_stroke (cr);
    transpose = FALSE;
}

void draw_dual_axis(cairo_t *cr, double max_x, double max_y, char *color)
{    
	cairo_color(cr, color);
    cairo_move_to (cr, max_x, -max_x);
    cairo_line_to (cr, -max_x, -max_x);
    cairo_move_to (cr, -max_y, max_y);
    cairo_line_to (cr, -max_y, -max_y);
    cairo_stroke (cr);
    transpose = TRUE;
}

double *transpose_data(double arr[], size_t arr_size, double max)
{
	for(int i = 0; i < arr_size; i++)
		arr[i] = -max + arr[i];
	return arr;
}

void plot_cairo(cairo_t *cr, double xarr[], double yarr[], size_t arr_size, double max_x, double max_y, char *color)
{
	cairo_color(cr, color);
	if(transpose == TRUE)
	{
	xarr = transpose_data(xarr, arr_size, max_x);
	yarr = transpose_data(yarr, arr_size, max_y);
	}

	for(int i = 0; i < arr_size; i++)
	    cairo_line_to(cr, xarr[i], yarr[i]);
	cairo_stroke(cr);
}

GtkWidget *create_graph_area(void *callback)
{
    GtkWidget *widget = gtk_drawing_area_new();
    g_signal_connect (G_OBJECT (widget), "draw", G_CALLBACK (callback), NULL);
    return widget;
}

void create_gdk_window(GtkWidget *widget, cairo_t *cr, char *color)
{
    GdkRectangle da;
    GdkWindow *window = gtk_widget_get_window(widget);
    gdk_window_get_geometry (window, &da.x, &da.y, &da.width, &da.height); // Determine GtkDrawingArea dimensions
    cairo_translate (cr, da.width / 2, da.height / 2);// Change the transformation matrix
    cairo_scale (cr, ZOOM_X, -ZOOM_Y);
    cairo_color(cr, color); // Draw on a black background 
    cairo_paint (cr);
}

void cairo_set_pixels_and_width(cairo_t *cr, double dx, double dy)
{
	cairo_device_to_user_distance (cr, &dx, &dy); // Determine the data points to calculate (ie. those in the clipping zone
    cairo_set_line_width (cr, dx);
}
