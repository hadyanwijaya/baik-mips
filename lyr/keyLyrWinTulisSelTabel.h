// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


void keyWinTulisSelTabel ()
{
  VAL_LABEL datx;
  VAL_LABEL valdat, tmpdat;

  int    n=0, i=0, j=0;
  int    idx=0;
  double k=0.0;
  int    col_num=0;

  char      class_tmpvar[MAX_STRING_LEN];
  char      **type;
  char      tmpstr[MAX_STRING_LEN];

  GtkTreeIter       iter;

  GtkTreeSelection  *selection;
  GtkTreeModel      *model;
  gboolean          success;

  gchar             *myval;
  GdkPixbuf         *pix[20];

  GtkWidget         *treeview;
  GtkListStore      *store;
  
  treeview  = NULL;
  store     = NULL;
  model     = NULL;
  type      = NULL;
  myval     = NULL;
 
  memset(&datx, '\0', sizeof(datx));
  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));
  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(&tmpstr, '\0', sizeof(tmpstr));

  // printf("TulisSelTabel\n");

           getlex();
           /* printf("%d %s\n",n, lex.detail.string); */

           if(lex.type == TYPE_IDENT) {
		     // printf("get type IDENT \n");

             if(currentClass != NULL && strlen(currentClass) > 0) {
               sprintf(class_tmpvar, "%s->%s", currentClass, lex.detail.ident);
               //printf("construct class var: %s\n", class_tmpvar);
               valdat = ValLabel( class_tmpvar, class_sub_deep, datx, VAL_FLAG_SEARCH_R );
             } else {
               valdat = ValLabel( lex.detail.ident, sub_deep, datx, VAL_FLAG_SEARCH_R );
             }

			 // printf("get type type %d with n %d\n", valdat.datatype, n);

             if(valdat.datatype == 40) {
                if(n == 0) {
				  if(valdat.widget == NULL) {
					Error("salah tulis_seltabel : tabel nil");
				  }

				  if(valdat.tblcoltype == NULL) {
					Error("salah tulis_seltabel : tipe kolom nil");
				  }

				  tmpdat    = valdat;
                  tmpdat.datatype = 40;

				  treeview  = valdat.widget;

 		          i = 0;
		          type = split(tmpdat.tblcoltype, "|");
                  while(type[i] != NULL && strlen(type[i]) > 0) {
				    // printf("type %d %s\n", i, type[i]);
				    pix[i] = NULL;
                    i++;
                  }
				  col_num = i;

				  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
				  model     = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
				  if(selection) {
				    // model = GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
                    success = gtk_tree_selection_get_selected(selection, NULL, &iter);

					// get data
					for(i = 0; i<col_num; i++) {
					  myval = NULL;
				      memset(&tmpstr, '\0', sizeof(tmpstr));
					  strcpy(tmpstr, type[i]);
					  if(!strcmp(tmpstr, "gambar") || !strcmp(tmpstr,"GAMBAR")) {
				        gtk_tree_model_get(model, &iter, i, &pix[i], -1);
					    printf("<GAMBAR%d>,",i);
					  } else {
				        gtk_tree_model_get(model, &iter, i, &myval, -1);
					    printf("%s,",myval);
					  }
					}
		            printf("\n");
				  }

                } 
             } else {
				 Error("Salah: Tulis_Sel_Tabel salah masukan");
			 }

           } else {
             Error("Salah: Tulis_Sel_Tabel salah masukan");
           }

  if(type != NULL)
    split_free(type);
}

