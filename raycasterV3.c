#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 //un grado en radiantes


//   Este código fué escrito para fines educativos y de recreación siguiendo principalmente
// la información encontrada en https://yewtu.be/watch?v=eOCQfxRQ2pY. Además de la fuente
// expuesta, también otros recursos fueron utilizados los cuales serán listados a continuación:
// https://lodev.org/cgtutor/raycasting.html
// https://yewtu.be/watch?v=eOCQfxRQ2pY
// http://www.advsys.net/ken/klab.htm
// https://yewtu.be/watch?v=vYgIKn7iDH8
// Probablemente más fuentes fueron consultadas pero no las anoté en el momento.
//
//   Al poner todo junto este código para un proyecto de mis estudios sentí la necesidad de
// hacer público el código y a la vez LIBRE. Es por eso que este proyecto va a estar bajo
// la licencia GNU-GPL_V3.

float px,py,pdx,pdy,pa,ojo,kroquis,rn,sAlt,fon; //posición del Espectador, rn=ray number

typedef struct {
	int w,a,s,d,o,k,v,b,n,m,f,q;
} ButtonKeys; ButtonKeys Keys;




void drawPlayer() {


//	if(kroquis==1){			//si el kroquis está activado...
//	glColor3f(0,0.8,0.4);	//color de la linea del Eje Visual
//	glLineWidth(3);		//tamaño de la linea del Eje Visual
//	glBegin(GL_LINES);
//	glVertex2i(px,py);
//	glVertex2i(px+pdx*10, py+pdy*10);
//	glEnd();
//	} else {
	glColor3f(0,0.8,0.4);	//color de la linea del Eje Visual
	glLineWidth(3);		//tamaño de la linea del Eje Visual
	glBegin(GL_LINES);
	glVertex2i(px,py);
	glVertex2i(px+pdx*5, py+pdy*5);
	glEnd();
//	}

//	glColor3f(0.9,0.8,0.2);	//color de la linea del Eje Visual
//	glLineWidth(3);		//tamaño de la linea del Eje Visual
//	glBegin(GL_LINES);
//	glVertex2i(px+pdy*10, px-pdx*10); //aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa
//	glVertex2i(px-pdy*10, px+pdx*10);
//	glEnd();

//	if(kroquis==1){
//	glColor3f(0,0.4,0.8);	//color del Punto de Visión
//	glPointSize(8);		//tamaño del Punto de Visión
//	glBegin(GL_POINTS);
//	glVertex2i(px,py);
//	glEnd();
//	} else {
	glColor3f(0,0.8,0.4);	//color del Punto de Visión
	glPointSize(8);		//tamaño del Punto de Visión
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();
//	}

	
//	if(kroquis==1){
//	glColor3f(0.8,0.5,0);	//color del Punto Principal
//	glPointSize(8);		//tamaño del Punto Principal
//	glBegin(GL_POINTS);
//	glVertex2i(px+pdx*10, py+pdy*10);
//	glEnd();
//	}

//	glColor3f(0.9,0.8,0.2);	//color de la linea del Eje Visual
//	glLineWidth(3);		//tamaño de la linea del Eje Visual
//	glBegin(GL_LINES);
//	glVertex2i(px+pdx*5, py+pdy*5);
//	glVertex2i(px-pdy*5, py+pdx*5);

//	glVertex2i(px-pdy*5, px-pdx*5);
//	glVertex2i(py+pdx*5, px-pdy*5);
//Este es el que va pero al revés

//	glVertex2i(px+pdy*10, px-pdx*10); //aaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa
//	glVertex2i(px-pdy*10, px+pdx*10);
//
//	glVertex2i(px+pdx*15, py-pdy*5);
//	glVertex2i(px-pdx*5, py+pdy*15);
	
//	glVertex2i(pdx+1+px*5, pdy-1+py*5);
//	glVertex2i(px+pdx*5, py+pdy*5);

//	glVertex2i(px+pdx*10, py+pdy*10);
//	glVertex2i(px+pdx*10, py+pdy*10);
//	glVertex2i(px+pdx*10, py+pdy*10);
//	glVertex2i(px*0.9+pdx*10, py*0.9+pdy*10);
//	glEnd();

}

int mapX=8,mapY=8,mapS=64;	//hace al mapa 8x8 y declara el total de casillas
int map[]= {
1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,1,
1,1,0,0,1,1,0,1,
1,0,0,0,0,1,0,1,
1,1,0,0,0,0,0,1,
1,0,0,0,0,0,0,1,
1,0,0,0,0,1,0,1,
1,1,1,1,1,1,1,1,
};

void drawMap2D() {
	int x,y,xo,yo;
	for (y=0;y<mapY;y++) {
		for (x=0;x<mapX;x++){
			if (map[y*mapX+x]==1) {
				glColor3f(0.4,0.4,0.4);		//color del interior de la cuadricula rellena
			}
			else {
				glColor3f(0,0,0);		//color del interior de la cuadricula vacía
			}
			xo=x*mapS;
			yo=y*mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo		+1,	yo	+1);
			glVertex2i(xo		+1,	yo+mapS	-1);
			glVertex2i(xo+mapS	-1,	yo+mapS	-1);
			glVertex2i(xo+mapS	-1,	yo	+1);
			glEnd();
		}
	}
}

float dist(float ax,float ay, float bx,float by, float ang){

	return ( sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );
// si se juega con esto se logra falsa profundidad y ojo de pez

}



void drawRays2D(){

	if (fon==1){
	glColor3f(0.7,0.7,0.7);		//color de techo
//	glColor3f(0.6,0,0.1);		//color de techo
//	glColor3f(0.2,0.1,0.6);		//color de techo
	glBegin(GL_POLYGON);
        glVertex2i(526,159);
	glVertex2i(526,0);
	glVertex2i(1006,0);
        glVertex2i(1006,159);
        glEnd();

//        glColor3f(0.5,0.1,0.1);		//color de piso
////      glColor3f(0.1,0.1,0.4);		//color de piso
//        glBegin(GL_POLYGON);
//        glVertex2i(526,320);
//        glVertex2i(526,159);
//        glVertex2i(1006,159);
//        glVertex2i(1006,320);
//        glEnd();
	}








	int r,mx,my,mp,dof; float rx,ry,ra,xo,yo,disT;
	ra=pa-DR*30; if(ra<0){ ra+=2*PI;} if(ra>2*PI){ ra-=2*PI;}
	for(r=0;r<rn;r++) {
		//---Constatar Lineas Horizontales---
		dof=0;
		float disH=1000000,hx=px,hy=py;
		float aTan=-1/tan(ra);
		if(ra>PI){ ry=(((int)py>>6)<<6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;} //mirando arriba
		if(ra<PI){ ry=(((int)py>>6)<<6)+64;     rx=(py-ry)*aTan+px; yo= 64; xo=-yo*aTan;} //mirando abajo

		if(ra==0 || ra==PI){ rx=px; ry=py; dof=8;} //mirando hacia derecha o izquerda
		while(dof<8) {
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;//error
			//8:46
			if (mp>0 && mp<mapX*mapY && map[mp]==1) { hx=rx; hy=ry; disH=dist(px,py,hx,hy,ra); dof=8;}
			else{ rx+=xo; ry+=yo; dof+=1;}//sigioente objetivo
		}
		//glColor3f(0,1,0); glLineWidth(10); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();
	
	

		//---Constatar Lineas Verticales---
		dof=0;
		float disV=1000000,vx=px,vy=py;
		float nTan=-tan(ra);
		if(ra>P2 && ra<P3){ rx=(((int)px>>6)<<6)-0.0001; ry=(px-rx)*nTan+py; xo=-64; yo=-xo*nTan;}//mirando izquierda
		if(ra<P2 || ra>P3){ rx=(((int)px>>6)<<6)+64;     ry=(px-rx)*nTan+py; xo= 64; yo=-xo*nTan;}//mirando derecha
		if(ra==0 || ra==PI){ rx=px; ry=py; dof=8;}//mirando hacia arriba o abajo
		while(dof<8) {
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;// pequeño error
			//8:46
			if (mp>0 && mp<mapX*mapY && map[mp]==1) { vx=rx; vy=ry; disV=dist(px,py,vx,vy,ra); dof=8;}
			else{ rx+=xo; ry+=yo; dof+=1;}//siguiente objetivo
		}
//aaaa	aaaa	if(disV<disH){ rx=vx; ry=vy; disT=disV; glColor3f(0.7,0,0.2);}			//choque con muro vertical
		if(disV<disH){ rx=vx; ry=vy; disT=disV; glColor3f(0.9,0,0.2);}			//choque con muro vertical

		if(disH<disV){ rx=hx; ry=hy; disT=disH; glColor3f(0.7,0,0.1);}			//choque con muro hrizontal
//		if(kroquis==1){
//			if(r==30){ glColor3f(0.2,0.3,0.2);}						//colorea EJE VISION
//		}
		glLineWidth(3); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();
		//---Dibujar los muros 3D---
		if(ojo==1){float ca=pa-ra; if(ca<0){ ca+=2*PI;} if(ca>2*PI){ ca-=2*PI;} disT=disT*cos(ca);}	//arregla el ojo de pez
		float lineH=(mapS*320)/disT; if(lineH>320){lineH=320;}				//alto de la linea
		float lineO=160-lineH/sAlt;							//invercion de linea IMP
		// lineo determina la altura de visión
		// lineh determina la altura de visión
//		if(px+pdx*50>lineH && py+pdy*50>lineH){glColor3f(0,0,0);};
//		Esto puede servir para un efecto de sombra tremendo
//		if(kroquis==1){
//			glColor3f(0.9,0.4,0.2);	//color del Punto de Visión
//			glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineO);glVertex2i(r*8+530,lineH+lineO);glEnd();
//		
//			glColor3f(0,0.4,0.8);	//color del Punto de Visión
//			glPointSize(8);		//tamaño del Punto de Visión
//			glBegin(GL_POINTS);
////			glVertex2i(r*8+530,lineO);
//			glVertex2i(r*8+530,lineH);
//			glEnd();
//		} else {
//			glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineO);glVertex2i(r*8+530,lineH+lineO);glEnd();
//		}
		if(kroquis==1){
//			glColor3f(0.9,0.4,0.2);	//color del Punto de Visión
			glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineO);glVertex2i(r*8+530,lineH+lineO);glEnd(); //dibujar lineas normales &

			glColor3f(0.2,0.3,0.2);	// Color de Linea de Tierra
			glPointSize(5);		// Grozor de Linea de Tierra
			glBegin(GL_POINTS);
//			glVertex2i(r*8+530,lineO);
			glVertex2i(r*8+530,160);
			glEnd();
		

//			if(ra>0){ if(ra<0.03){	//dibujar Punto de Fuga del Este
//			glColor3f(0.8,0.5,0);	// Color del Punto de Fuga del Este
//			glPointSize(8);		// Tamaño del Punto de Fuga
//			glBegin(GL_POINTS);
//			glVertex2i(r*8+530,160);
//			glEnd();
//			}}

//			if(ra>1.58){ if(ra<1.60){	//dibujar Punto de Fuga del Sur
//			glColor3f(0.8,0.5,0);	// Color del Punto de Fuga del Sur
//			glPointSize(8);		// Tamaño del Punto de Sur
//			glBegin(GL_POINTS);
//			glVertex2i(r*8+530,160);
//			glEnd();
//			}}

//			if(ra>3.10){ if(ra<3.13){	//dibujar Punto de Fuga del Oeste
//			glColor3f(0.8,0.5,0);	// Color del Punto de Fuga del Oeste
//			glPointSize(8);		// Tamaño del Punto de Oeste
//			glBegin(GL_POINTS);
//			glVertex2i(r*8+530,160);
//			glEnd();
//			}}

//			if(ra>4.68){ if(ra<4.70){	//dibujar Punto de Fuga del Norte
//			glColor3f(0.8,0.5,0);	// Color del Punto de Fuga del Norte
//			glPointSize(8);		// Tamaño del Punto de Norte
//			glBegin(GL_POINTS);
//			glVertex2i(r*8+530,160);
//			glEnd();
//			}}


			if(	ra>4.68 && ra<4.70 ||
				ra>3.10 && ra<3.13 ||
				ra>1.58 && ra<1.60 ||	
				ra>0 && ra<0.03
					){
			glColor3f(0.8,0.5,0);	// Color del Punto de Fuga General
			glPointSize(8);		// Tamaño del Punto General
			glBegin(GL_POINTS);
			glVertex2i(r*8+530,160);
			glEnd();
			}


		} else {
			glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineO);glVertex2i(r*8+530,lineH+lineO);glEnd();
		}


		ra+=DR; if(ra<0){ ra+=2*PI;} if(ra>2*PI){ ra-=2*PI;}
	}
}


float frame1,frame2,fps;

void display () {		//esto es lo que se va a mostrar en la pantalla
	
	frame2=glutGet(GLUT_ELAPSED_TIME); fps=(frame2-frame1); frame1=glutGet(GLUT_ELAPSED_TIME);


	//TECLAS
	if(Keys.a==1){ pa-=0.004*fps; if(pa<   0){ pa+=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
	if(Keys.d==1){ pa+=0.004*fps; if(pa>2*PI){ pa-=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
//	if(Keys.w==1){ px+=pdx*0.02*fps; py+=pdy*0.02*fps;}
//	if(Keys.s==1){ px-=pdx*0.02*fps; py-=pdy*0.02*fps;}

	int xo=0; if(pdx<0){ xo=-20;} else{xo=20;}      //encontrar posiciones para detectar la colición
	int yo=0; if(pdy<0){ yo=-20;} else{yo=20;}
	int ipx=px/64.0, ipx_add_xo=(px+xo)/64.0, ipx_sub_xo=(px-xo)/64.0;
	int ipy=py/64.0, ipy_add_yo=(py+yo)/64.0, ipy_sub_yo=(py-yo)/64.0;
	if(Keys.w==1){
		if (map[ipy*mapX        + ipx_add_xo    ]==0){px+=pdx*0.03*fps;}
		if (map[ipy_add_yo*mapX + ipx           ]==0){py+=pdy*0.03*fps;}
	}

	if(Keys.s==1){
		if (map[ipy*mapX        + ipx_sub_xo    ]==0){px-=pdx*0.03*fps;}
		if (map[ipy_sub_yo*mapX + ipx           ]==0){py-=pdy*0.03*fps;}
	}



	
	//OJO DE PEZ
      	if(Keys.o==1){ if(ojo==1){ojo=0;} else if(ojo==0){ojo=1;} } 

      	//KROQUIS
	if(Keys.k==1){ if(kroquis==1){kroquis=0;} else if(kroquis==0){kroquis=1;} } 

      	//NUMERO DE LINEAS
	if(Keys.v==1){ rn-=1; if(rn<0){ rn=0;}}
	if(Keys.b==1){ rn+=1; if(rn>60){rn=60;}}

     	 //VISTA DE SAPO Y ALTURA
	if(Keys.n==1){ sAlt-=1; if(sAlt<1) { sAlt=1;}}
	if(Keys.m==1){ sAlt+=1; if(sAlt>10){sAlt=10;}}

      	//FONDO
	if(Keys.f==1){ if(fon==1){fon=0;} else if(fon==0){fon=1;} } 

	//SALIR
	if(Keys.q==1){ exit(0);}
	glutPostRedisplay();





	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawRays2D();
	drawPlayer();
	glutSwapBuffers ();

}

//void SpeButtons(unsigned char key, int x, int y) {
//        //OJO DE PEZ
//        if(key=='o'){ if(ojo==1){ojo=0;} else if(ojo==0){ojo=1;} }
//
//        //KROQUIS
//        if(key=='k'){ if(kroquis==1){kroquis=0;} else if(kroquis==0){kroquis=1;} }
//
//        //NUMERO DE LINEAS
//        if(key=='v'){ rn-=1; if(rn<0){ rn=0;}}
//        if(key=='b'){ rn+=1; if(rn>60){rn=60;}}
//
//        //VISTA DE SAPO Y ALTURA
//        if(key=='n'){ sAlt-=1; if(sAlt<1) { sAlt=1;}}
//        if(key=='m'){ sAlt+=1; if(sAlt>10){sAlt=10;}}
//
//        //FONDO
//	if(key=='f'){ if(fon==1){fon=0;} else if(fon==0){fon=1;} }
//        
//	//SALIR
//	if(key=='q'){ exit(0);}
//	glutPostRedisplay();
//
//}


void ButtonDown(unsigned char key,int x,int y) {
	if(key=='a'){Keys.a=1;}
	if(key=='d'){Keys.d=1;}
	if(key=='s'){Keys.s=1;}
	if(key=='w'){Keys.w=1;}

	if(key=='o'){Keys.o=1;}	// TODO: Es necesario encontrar la forma de que no se presione muchas veces
	if(key=='k'){Keys.k=1;}
	if(key=='v'){Keys.v=1;}
	if(key=='b'){Keys.b=1;}

	if(key=='n'){Keys.n=1;}
	if(key=='m'){Keys.m=1;}
	if(key=='f'){Keys.f=1;}
	if(key=='q'){Keys.q=1;}

	glutPostRedisplay();
}

void ButtonUp(unsigned char key,int x,int y){
	if(key=='a'){Keys.a=0;}
	if(key=='d'){Keys.d=0;}
	if(key=='s'){Keys.s=0;}
	if(key=='w'){Keys.w=0;}

	if(key=='o'){Keys.o=0;}
	if(key=='k'){Keys.k=0;}
	if(key=='v'){Keys.v=0;}
	if(key=='b'){Keys.b=0;}

	if(key=='n'){Keys.n=0;}
	if(key=='m'){Keys.m=0;}
	if(key=='f'){Keys.f=0;}
	if(key=='q'){Keys.q=0;}

	glutPostRedisplay();
}



void init () {
	glClearColor(0.1,0.1,0.1,0);
	gluOrtho2D(0,1024,512,0);
	px=200; py=300; pdx=cos(pa)*5; pdy=sin(pa)*5;
	rn=0;
	sAlt=2;
}

void resize(int w,int h) {
	glutReshapeWindow(1024,512); //tamaño de la ventana
}

int main (int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 512);
//	glutInitWindowPosition(200,200); //centrar ventana
	glutCreateWindow("Pers. RayCaster - Imp. 2022");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);	//Fija el tamaño de la ventana
//	glutKeyboardFunc(SpeButtons);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);

	glutMainLoop();
}
