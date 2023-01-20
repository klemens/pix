/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  Pix
 *
 *  Copyright (C) 2010 The Free Software Foundation, Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include <gtk/gtk.h>
#include <pix.h>
#include "dlg-comments-preferences.h"
#include "preferences.h"


typedef struct {
	GtkBuilder *builder;
	GSettings  *settings;
	GtkWidget  *dialog;
} DialogData;


static void
destroy_cb (GtkWidget  *widget,
	    DialogData *data)
{
	g_object_unref (data->builder);
	g_object_unref (data->settings);
	g_free (data);
}


static void
sync_checkbutton_clicked_cb (GtkWidget  *widget,
			     DialogData *data)
{
	g_settings_set_boolean (data->settings,
			        PREF_COMMENTS_SYNCHRONIZE,
			        gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (gtk_builder_get_object (data->builder, "sync_checkbutton"))));
}


void
dlg_comments_preferences (GtkWindow *parent)
{
	DialogData *data;

	data = g_new0 (DialogData, 1);
	data->builder = _gtk_builder_new_from_file ("comments-preferences.ui", "comments");
	data->settings = g_settings_new (PIX_COMMENTS_SCHEMA);

	/* Get the widgets. */

	data->dialog = g_object_new (GTK_TYPE_DIALOG,
				     "title", _("Preferences"),
				     "transient-for", GTK_WINDOW (parent),
				     "modal", TRUE,
				     "destroy-with-parent", FALSE,
				     "use-header-bar", _gtk_settings_get_dialogs_use_header (),
				     NULL);
	gtk_container_add (GTK_CONTAINER (gtk_dialog_get_content_area (GTK_DIALOG (data->dialog))),
			   _gtk_builder_get_widget (data->builder, "dialog_content"));
	gtk_dialog_add_buttons (GTK_DIALOG (data->dialog),
				_GTK_LABEL_OK, GTK_RESPONSE_CLOSE,
				NULL);

	/* Set widgets data. */

	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (gtk_builder_get_object (data->builder, "sync_checkbutton")),
				      g_settings_get_boolean (data->settings, PREF_COMMENTS_SYNCHRONIZE));

	/* Set the signals handlers. */

	g_signal_connect (G_OBJECT (data->dialog),
			  "destroy",
			  G_CALLBACK (destroy_cb),
			  data);
	g_signal_connect_swapped (gtk_dialog_get_widget_for_response (GTK_DIALOG (data->dialog), GTK_RESPONSE_CLOSE),
				  "clicked",
				  G_CALLBACK (gtk_widget_destroy),
				  G_OBJECT (data->dialog));
	g_signal_connect (gtk_builder_get_object (data->builder, "sync_checkbutton"),
			  "clicked",
			  G_CALLBACK (sync_checkbutton_clicked_cb),
			  data);

	/* run dialog. */

	gtk_widget_show (data->dialog);
}
