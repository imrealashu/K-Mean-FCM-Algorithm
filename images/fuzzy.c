#include<stdio.h>
#include<malloc.h>
#include<math.h>

#define C 4
#define m 2
#define THRESHOLD 0.001

int *x, *seg, MAX_VAL, bakiHai;
float *c, **dij;
long int N;

float calc_membership_of_pixel_i_to_cluster_j(int i, int j){
	float d = 0.0; int k;

	for(k = 0; k < C; k++){
		d += (x[i] - c[k] == 0.0) ? 0.0 : pow((fabs(x[i] - c[j]) / fabs(x[i] - c[k])), (2/(m-1)));
	}
	return (d == 0.0) ? 0 : (1/d);
}

void calc_membership(){
	int i, j;
	
	for(i = 0; i < N; i++)
		for(j = 0; j < C; j++)
			dij[i][j] = calc_membership_of_pixel_i_to_cluster_j(i,j);
}

float calc_center_vector_of_cluster(int j){
	float numerator = 0.0, denominator = 0.0;
	int i;
	
	for(i = 0; i < N; i++){
		numerator += pow(dij[i][j], m) * x[i];
		denominator += pow(dij[i][j], m);
	}
	return (numerator / denominator);
}

void calc_new_clusters(){
	int j, temp_vector;
	
	bakiHai = 1;
	for(j = 0; j < C; j++){
		temp_vector = calc_center_vector_of_cluster(j);
		if(fabs(temp_vector - c[j]) > THRESHOLD) bakiHai++;
		c[j] = temp_vector;
	}		
	bakiHai -= 1;
}

void Fuzzy_cMeans(){
	int i = 0;

	while(bakiHai){
		calc_membership();
		calc_new_clusters();
	}
}

int getCluster(int i){
	int j, max_j = 0; float max = 0.0;

	for(j = 0; j < C; j++)
		if(max < dij[i][j]){
			max = dij[i][j];
			max_j = j;
		}
	seg[i] = max_j;
	return (int) c[max_j];
}

int main(int argc, char **argv){

	FILE *R; char str[20]; int row = 0, col = 0;

	int i, j, k, pixel_val, accuracy, faulty, gm, faulty_gm, xx, csf , yy, faulty_csf, zz, wm, faulty_wm, bg, faulty_bg, ww;
	
	R= fopen(argv[1],"r+");

	fscanf(R, "%s", str);
	fscanf(R, "%s", str);
	fscanf(R, "%d", &col);
	fscanf(R, "%d", &row);
	fscanf(R, "%d", &MAX_VAL);

	N = row * col;
	x = (int *) malloc(sizeof(int) * N);
	seg = (int *) malloc(sizeof(int) * N);
	c = (float *) malloc(sizeof(float) * C);
	dij= (float **) malloc(sizeof(float *) * N);
	for(i = 0; i < N; i++) dij[i] = (float *) malloc(sizeof(float) * C);

	for(i =0; i < N; i++)
		fscanf(R, "%d", &x[i]);

	c[0] = 10;
	for(i = 1; i < C; i++)
		c[i] = c[i-1] + ((MAX_VAL)/C);

	bakiHai = 1;
	fclose(R);

	// printf("\n\nInitial Clusters:: ");
	// for(i=0; i<C; i++)
	// 	printf("  %f", c[i]);

	// printf("\nWorking... .. .");
	Fuzzy_cMeans();
	//printf("  done!");

	// printf("\n\nFinal Clusters:: ");
	// for(i=0; i<C; i++)
	// 	printf("  %f", c[i]);

	R = fopen("res.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);

	for(i = 0; i < N; i++)
		fprintf(R, "%d ", getCluster(i));
		
	fclose(R);


	R = fopen("cluster.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);

	for(i = 0; i < N; i++)
		fprintf(R, "%d ", seg[i]);
		
	fclose(R);

	
	R = fopen("seg0.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++)
		fprintf(R, "%d ", (seg[i] == 0) ? 0 : 255);
	fclose(R);

	R = fopen("seg1.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++)
		fprintf(R, "%d ", (seg[i] == 1) ? 0 : 255);
	fclose(R);

	R = fopen("seg2.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++)
		fprintf(R, "%d ", (seg[i] == 2) ? 0 : 255);
	fclose(R);

	R = fopen("seg3.pgm","w+");
	fprintf(R, "P2\n#\n");
	fprintf(R, "%d %d\n%d\n", col, row, MAX_VAL);
	for(i = 0; i < N; i++)
		fprintf(R, "%d ", (seg[i] == 3) ? 0 : 255);
	fclose(R);


	if(argc > 2){
		R = fopen(argv[2],"r");
		fscanf(R, "%s", str);
		fscanf(R, "%s", str);
		fscanf(R, "%d", &col);
		fscanf(R, "%d", &row);
		fscanf(R, "%d", &MAX_VAL);
		
		k = 0; accuracy = faulty = gm = faulty_gm = xx = csf = yy = faulty_csf = zz = wm = faulty_wm = bg = faulty_bg = ww = 0;
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
			            if(seg[ww]== pixel_val) bg++;
			            else faulty_bg++;
			          }
			        ww++;
					if(pixel_val < 2 && pixel_val > 0){
						if(seg[xx]== pixel_val) gm++;
						else faulty_gm++;
					}
					xx++;

					if(pixel_val < 3 && pixel_val > 1){
						if(seg[yy]== pixel_val) csf++;
						else faulty_csf++;
					}
					yy++;

					if(pixel_val < 4 && pixel_val > 2){
						if(seg[zz]== pixel_val) wm++;
						else faulty_wm++;
					}
					zz++;
				}
		fclose(R);
		printf("%.2f",(((float)(bg+gm+csf+wm)*100)/((float)(bg+gm+csf+wm)+(faulty_bg+faulty_csf+faulty_wm+faulty_gm))));
		printf("#%.2f", (((float)gm*100)/((float)gm+faulty_gm)));//grey matter
		printf("#%.2f", (((float)csf*100)/((float)csf+faulty_csf)));//csf
		printf("#%.2f", (((float)wm*100)/((float)wm+faulty_wm)));//white matter
		printf("#%.2f", (((float)wm*100)/((float)bg+faulty_bg)));//Background
	}
	
	return 0;
}