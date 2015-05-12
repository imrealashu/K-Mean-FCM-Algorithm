#include<stdio.h>
#include<malloc.h>
#include<math.h>

#define C 4
#define m 2
#define THRESHOLD 0.001

int *x, *seg, MAX_VAL, bakiHai, index_c[4];
float c[4], **ci;
long int N;

typedef struct 
{
	int i;
	int j;
}pixel;

void allocate_points(){
	float d[4];
	int i, k, min, min_i;
	index_c[0] = index_c[1] = index_c[2] = index_c[3] = 0;
	for(i=0; i<N; i++){
		d[0] = fabs(c[0]-x[i]);
		d[1] = fabs(c[1]-x[i]);
		d[2] = fabs(c[2]-x[i]);	
		d[3] = fabs(c[3]-x[i]);
		min = 999; min_i = 0;
		for(k=0; k < 4; k++){
			if(d[k]< min){
				min = d[k];
				min_i = k;
			}
		}
		index_c[min_i]++;
		ci[min_i][index_c[min_i]] = x[i];
		seg[i] = min_i;
	}
}

void calc_cluster(){
	int i,j;
	float sum, avg, temp;
	bakiHai = 0;
	for(i=0; i<4; i++){
		sum = avg = 0;
		for(j = 0; j < index_c[i]; j++){
			sum+= ci[i][j];
		}
		temp = (index_c[i] == 0) ? c[i] : (sum / index_c[i]);
		if(fabs(temp - c[i]) > THRESHOLD) bakiHai++;
		c[i] = temp;
	}
}

void kMeans(){
	int i = 0;
	while(bakiHai){
		allocate_points();
		calc_cluster();
	}
}


int main(int argc, char **argv){

	FILE *R; char str[20]; int row = 0, col = 0;

	int i, j, k, pixel_val, accuracy, faulty;
	
	R= fopen(argv[1],"r+");

	fscanf(R, "%s", str);
	fscanf(R, "%s", str);
	fscanf(R, "%d", &col);
	fscanf(R, "%d", &row);
	fscanf(R, "%d", &MAX_VAL);

	N = row * col;
	x = (int *) malloc(sizeof(int) * N);
	seg = (int *) malloc(sizeof(int) * N);
	
	ci= (float **) malloc(sizeof(float *) * N);
	for(i = 0; i < N; i++) ci[i] = (float *) malloc(sizeof(float) * N);

	index_c[0] = index_c[1] = index_c[2] = index_c[3] = 0;

	for(i =0; i < N; i++)
		fscanf(R, "%d", &x[i]);

	c[0] = 10;
	for(i = 1; i < C; i++)
		c[i] = c[i-1] + ((MAX_VAL)/C);

	bakiHai = 1;
	fclose(R);

	//printf("\n\nInitial Clusters:: ");
	// for(i=0; i<C; i++)
	// 	printf("  %f", c[i]);

	//printf("\nWorking... .. .");
	kMeans();
	//printf("  done!");

	//printf("\n\nFinal Clusters:: ");
	// for(i=0; i<C; i++)
	// 	printf("  %f", c[i]);

	R = fopen("res.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);

	for(i = 0; i < N; i++)
		fprintf(R, "%d ", abs(c[seg[i]]));
		
	fclose(R);


	R = fopen("cluster.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);

	for(i = 0; i < N; i++)
		fprintf(R, "%d ", seg[i]);
		
	fclose(R);

	int a_wm, a_gm, a_csf, a_bg, f_wm, f_gm, f_csf, f_bg;
	a_wm = a_gm = a_csf = a_bg = f_wm = f_gm = f_csf = f_bg = 0;

	R = fopen("seg0.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++){
		if(seg[i] == 0){
			fprintf(R, "%d ",0);
			// a_bg++;
		}else{
			fprintf(R, "%d ", 255);
			// f_bg++;
		}
	
	}
		
	fclose(R);

	R = fopen("seg1.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++){
		if(seg[i] == 1){
			fprintf(R, "%d ",0);
			// a_gm++;
		}else{
			fprintf(R, "%d ", 255);
			// f_gm++;
		}
	
	}
	fclose(R);

	R = fopen("seg2.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++){
		if(seg[i] == 2){
			fprintf(R, "%d ",0);	
			// a_csf++;
		}else{
			fprintf(R, "%d ", 255);
			// f_csf++;
		}
	
	}
	fclose(R);

	R = fopen("seg3.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++){
		if(seg[i] == 3){
			fprintf(R, "%d ",0);	
			// a_wm++;
		}else{
			fprintf(R, "%d ", 255);
			// f_wm++;
		}
	
	}
	fclose(R);


	if(argc > 2){
		R = fopen(argv[2],"r");
		fscanf(R, "%s", str);
		fscanf(R, "%s", str);
		fscanf(R, "%d", &col);
		fscanf(R, "%d", &row);
		fscanf(R, "%d", &MAX_VAL);
		int ww, xx,yy,zz;
		ww = xx = yy = zz = 0;
		k = 0; accuracy = faulty = 0;
		for(i = 0; i < col; i++)
			for(j = 0; j < row; j++)
				{
					fscanf(R, "%d", &pixel_val);
					// if(pixel_val < 4){
					// 	if(seg[k] == pixel_val) accuracy++;
					// 	else faulty++;
					// }
					// k++;
					if(pixel_val < 1){
						if(seg[ww]== pixel_val) a_bg++;
						else f_bg++;
					}
					ww++;
					if(pixel_val < 2 && pixel_val > 0){
						if(seg[xx]== pixel_val) a_gm++;
						else f_gm++;
					}
					xx++;

					if(pixel_val < 3 && pixel_val > 1){
						if(seg[yy]== pixel_val) a_csf++;
						else f_csf++;
					}
					yy++;

					if(pixel_val < 4 && pixel_val > 2){
						if(seg[zz]== pixel_val) a_wm++;
						else f_wm++;
					}
					zz++;
				}
		fclose(R);
		printf("%.2f", (((float)(a_bg+a_gm+a_csf+a_wm)*100)/((float)(a_bg+a_gm+a_csf+a_wm)+(f_bg+f_gm+f_csf+f_wm))));
		printf("#%.2f", (((float)a_gm*100)/((float)a_gm+f_gm)));
		printf("#%.2f", (((float)a_csf*100)/((float)a_csf+f_csf)));
		printf("#%.2f", (((float)a_wm*100)/((float)a_wm+f_wm)));
		printf("#%.2f", (((float)a_bg*100)/((float)a_bg+f_bg)));
	}
	
	return 0;
}