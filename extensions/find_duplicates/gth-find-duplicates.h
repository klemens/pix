/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/*
 *  Pix
 *
 *  Copyright (C) 2010 Free Software Foundation, Inc.
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

#ifndef GTH_FIND_DUPLICATES_H
#define GTH_FIND_DUPLICATES_H

#include <glib-object.h>
#include <pix.h>

#define GTH_TYPE_FIND_DUPLICATES                (gth_find_duplicates_get_type ())
#define GTH_FIND_DUPLICATES(o)           	(G_TYPE_CHECK_INSTANCE_CAST ((o), GTH_TYPE_FIND_DUPLICATES, GthFindDuplicates))
#define GTH_FIND_DUPLICATES_CLASS(k)     	(G_TYPE_CHECK_CLASS_CAST ((k), GTH_TYPE_FIND_DUPLICATES, GthFindDuplicatesClass))
#define GTH_IS_FIND_DUPLICATES_DIALOG(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GTH_TYPE_FIND_DUPLICATES))
#define GTH_IS_FIND_DUPLICATES_DIALOG_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GTH_TYPE_FIND_DUPLICATES))
#define GTH_FIND_DUPLICATES_GET_CLASS(o) 	(G_TYPE_INSTANCE_GET_CLASS((o), GTH_TYPE_FIND_DUPLICATES, GthFindDuplicatesClass))

typedef struct _GthFindDuplicates         GthFindDuplicates;
typedef struct _GthFindDuplicatesPrivate  GthFindDuplicatesPrivate;
typedef struct _GthFindDuplicatesClass    GthFindDuplicatesClass;

struct _GthFindDuplicates
{
	GObject __parent;
	GthFindDuplicatesPrivate *priv;
};

struct _GthFindDuplicatesClass
{
	GObjectClass __parent_class;
};

GType   gth_find_duplicates_get_type (void) G_GNUC_CONST;
void    gth_find_duplicates_exec            (GthBrowser *browser,
					     GFile      *location,
					     gboolean    recursive,
					     const char *filter);

#endif /* GTH_FIND_DUPLICATES_H */
