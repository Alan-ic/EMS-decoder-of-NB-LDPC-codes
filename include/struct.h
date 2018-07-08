#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

/*!
 * \file struct.h
 * \brief header for structures
 */

//! \struct GF_element
typedef struct
{
    int GF;
    float LLR;
} GF_element;

//! \struct syndrome_type
typedef struct
{
    int GF;
    float LLR;
    int config; //config number
} syndrome_type;

//! \struct GF_syndrome_type
typedef struct
{
    float min1;
    float min2;
    float min3;
    float min4;
    int index1;
    int index2;
    int index3;
    float LLR;
} GF_syndrome_type;



/******************************************************/
/****************** LDPC code description**************/
/******************************************************/
/*! \struct code_t
*  \brief LDPC code parameters
* The parity-check matrix has a sparse description.
* ce type contient les param�tres du code LDPC consid�r�. Ces param�tres sont collect�s depuis un fichier texte contenant la matrice
* de parit� du code.
*/
typedef struct
{
    int N;			/* number of columns in H */
    int M;			/* number of rows in H */
    int K;			/* number of information symbols : K = N-M */
    int GF;			/* Field order (eg. GF=256) */
    int logGF;		/* logGF = log2(GF)  ( given GF = 2^q => logGF = q) : logGF is the number of bits forming GF symbols */
    int **mat;		/* the Parity-check matrix : tableau bidimensionnel contenant les VN (i.e les colonnes) qui participe dans chaque contrainte
					   de parit�  (i.e les lignes) */
    int **matValue;		/* Parity-check matrix non-binary coefficients : contient les coefficient GF(q) pour chaque ligne */
    int *rowDegree;		/* rowDegree[i] = the i^th check node degree */
    int *columnDegree; 	/* columnDegree[j] = the j^th variable node degree */
     int nbBranch;		/* number of edges in the Tanner graph */
    float rate; 		/* Code rate */
    int **matUT;		/* Upper Triangular form of the parity-check matrix after Gaussian elimination. matUT is used for encoding*/
    int *Perm;		/* Permutation used for Gaussian Elimination  */
} code_t;


/*!
* \struct table_t
* \brief Computation tables in GF(q)
*/
typedef struct
{
    int **BINGF;		/* Mapping symbol GFq -> ensemble de symboles binaires */
    int **ADDGF;		/* Addition table in GFq */
    int **MULGF;		/* Multiplication table in GFq */
    int **DIVGF;		/* Division table in GFq */
} table_t;

/** *************************************************************************/
/******************************** EMS decoder********************************/
/*** Structure for the messages on the edges on decoding graph intrinsic_LLR ***/
/****************************************************************************/
typedef float softdata_t ; /* la fiabilit� d'un message est de type float */

/*!
* \struct decoder_t
* \brief decoder parameter and values
*/
typedef struct
{
    int N;
    int nbMax; /* c'est le param�tre nm dans l'algo EMS : Au lieu de transmettre les q symbole dans GF(q), on fait une trancature et on transmet
				uniquement les nm plus fiables symboles */
    int nbBranch; /* nombre de branches dans le graphe de Tanner */
    softdata_t 	**CtoV;		/* An array to store the nbMax largest Check_to_Variable reliabilities for all edges on the graph
							CtoV Array size = (nbBranch x nbMax) */
    softdata_t 	**intrinsic_LLR;	   /* An array to store intrinsic Log intrinsic_LLR Ratios received from channel. Each variable node has GF intrinsic
                                      LLRs. So, the size of intrinsic_LLR is (N x GF) where N is the number of VNs and GF is the order of the Galois
                                      field. The values are sorted in decreasing way */
    int 		**intrinsic_GF; /*  Galois field symbols associated to the LLRs values in 'intrinsic_LLR'
										Same size as for 'intrinsic_LLR' */
    softdata_t 	**APP;		/* Array to store A Posteriori Probability used to make hard decision on symbol value
						       Same size as for 'intrinsic_LLR'*/
    softdata_t      **M_VtoC_LLR; //LLR inputs to one Check node processor.
    int             **M_VtoC_GF; //GF index corresponding to M_VtoC_LLR.
    softdata_t      **M_CtoV_LLR ; //LLR output from one Check node processor.
    int             **M_CtoV_GF; //GF index corresponding to M_VtoC_LLR.
} decoder_t;





/*!
 *
 * \brief Binary image of the field GF(16)
 * Primitive polynomial used P(x)=X^4+X+1 (GF(16))
  */
static const int BinGF_16[16][4]=
{
    {0,0,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,0,0},
    {0,1,1,0},
    {0,0,1,1},
    {1,1,0,1},
    {1,0,1,0},
    {0,1,0,1},
    {1,1,1,0},
    {0,1,1,1},
    {1,1,1,1},
    {1,0,1,1},
    {1,0,0,1}
};




/*!
 *
 * \brief Binary image of the field GF(64)
 * Primitive polynomial used P(x)=X^6+X+1 (GF(64))
 */
static const int BinGF_64[64][6]=
{
    {0,0,0,0,0,0},
    {1,0,0,0,0,0},
    {0,1,0,0,0,0},
    {0,0,1,0,0,0},
    {0,0,0,1,0,0},
    {0,0,0,0,1,0},
    {0,0,0,0,0,1},
    {1,1,0,0,0,0},
    {0,1,1,0,0,0},
    {0,0,1,1,0,0},
    {0,0,0,1,1,0},
    {0,0,0,0,1,1},
    {1,1,0,0,0,1},
    {1,0,1,0,0,0},
    {0,1,0,1,0,0},
    {0,0,1,0,1,0},
    {0,0,0,1,0,1},
    {1,1,0,0,1,0},
    {0,1,1,0,0,1},
    {1,1,1,1,0,0},
    {0,1,1,1,1,0},
    {0,0,1,1,1,1},
    {1,1,0,1,1,1},
    {1,0,1,0,1,1},
    {1,0,0,1,0,1},
    {1,0,0,0,1,0},
    {0,1,0,0,0,1},
    {1,1,1,0,0,0},
    {0,1,1,1,0,0},
    {0,0,1,1,1,0},
    {0,0,0,1,1,1},
    {1,1,0,0,1,1},
    {1,0,1,0,0,1},
    {1,0,0,1,0,0},
    {0,1,0,0,1,0},
    {0,0,1,0,0,1},
    {1,1,0,1,0,0},
    {0,1,1,0,1,0},
    {0,0,1,1,0,1},
    {1,1,0,1,1,0},
    {0,1,1,0,1,1},
    {1,1,1,1,0,1},
    {1,0,1,1,1,0},
    {0,1,0,1,1,1},
    {1,1,1,0,1,1},
    {1,0,1,1,0,1},
    {1,0,0,1,1,0},
    {0,1,0,0,1,1},
    {1,1,1,0,0,1},
    {1,0,1,1,0,0},
    {0,1,0,1,1,0},
    {0,0,1,0,1,1},
    {1,1,0,1,0,1},
    {1,0,1,0,1,0},
    {0,1,0,1,0,1},
    {1,1,1,0,1,0},
    {0,1,1,1,0,1},
    {1,1,1,1,1,0},
    {0,1,1,1,1,1},
    {1,1,1,1,1,1},
    {1,0,1,1,1,1},
    {1,0,0,1,1,1},
    {1,0,0,0,1,1},
    {1,0,0,0,0,1},
};


/*! Binary image of field GF(256)
* Primitive polynomial used P(x) = P(x)=X^8+X^4+X^3+X^2+1 (GF(256))
*/
static const int BinGF_256[256][8]={
{0,	0,	0,	0,	0,	0,	0,	0},
{1,	0,	0,	0,	0,	0,	0,	0},
{0,	1,	0,	0,	0,	0,	0,	0},
{0,	0,	1,	0,	0,	0,	0,	0},
{0,	0,	0,	1,	0,	0,	0,	0},
{0,	0,	0,	0,	1,	0,	0,	0},
{0,	0,	0,	0,	0,	1,	0,	0},
{0,	0,	0,	0,	0,	0,	1,	0},
{0,	0,	0,	0,	0,	0,	0,	1},
{1,	0,	1,	1,	1,	0,	0,	0},
{0,	1,	0,	1,	1,	1,	0,	0},
{0,	0,	1,	0,	1,	1,	1,	0},
{0,	0,	0,	1,	0,	1,	1,	1},
{1,	0,	1,	1,	0,	0,	1,	1},
{1,	1,	1,	0,	0,	0,	0,	1},
{1,	1,	0,	0,	1,	0,	0,	0},
{0,	1,	1,	0,	0,	1,	0,	0},
{0,	0,	1,	1,	0,	0,	1,	0},
{0,	0,	0,	1,	1,	0,	0,	1},
{1,	0,	1,	1,	0,	1,	0,	0},
{0,	1,	0,	1,	1,	0,	1,	0},
{0,	0,	1,	0,	1,	1,	0,	1},
{1,	0,	1,	0,	1,	1,	1,	0},
{0,	1,	0,	1,	0,	1,	1,	1},
{1,	0,	0,	1,	0,	0,	1,	1},
{1,	1,	1,	1,	0,	0,	0,	1},
{1,	1,	0,	0,	0,	0,	0,	0},
{0,	1,	1,	0,	0,	0,	0,	0},
{0,	0,	1,	1,	0,	0,	0,	0},
{0,	0,	0,	1,	1,	0,	0,	0},
{0,	0,	0,	0,	1,	1,	0,	0},
{0,	0,	0,	0,	0,	1,	1,	0},
{0,	0,	0,	0,	0,	0,	1,	1},
{1,	0,	1,	1,	1,	0,	0,	1},
{1,	1,	1,	0,	0,	1,	0,	0},
{0,	1,	1,	1,	0,	0,	1,	0},
{0,	0,	1,	1,	1,	0,	0,	1},
{1,	0,	1,	0,	0,	1,	0,	0},
{0,	1,	0,	1,	0,	0,	1,	0},
{0,	0,	1,	0,	1,	0,	0,	1},
{1,	0,	1,	0,	1,	1,	0,	0},
{0,	1,	0,	1,	0,	1,	1,	0},
{0,	0,	1,	0,	1,	0,	1,	1},
{1,	0,	1,	0,	1,	1,	0,	1},
{1,	1,	1,	0,	1,	1,	1,	0},
{0,	1,	1,	1,	0,	1,	1,	1},
{1,	0,	0,	0,	0,	0,	1,	1},
{1,	1,	1,	1,	1,	0,	0,	1},
{1,	1,	0,	0,	0,	1,	0,	0},
{0,	1,	1,	0,	0,	0,	1,	0},
{0,	0,	1,	1,	0,	0,	0,	1},
{1,	0,	1,	0,	0,	0,	0,	0},
{0,	1,	0,	1,	0,	0,	0,	0},
{0,	0,	1,	0,	1,	0,	0,	0},
{0,	0,	0,	1,	0,	1,	0,	0},
{0,	0,	0,	0,	1,	0,	1,	0},
{0,	0,	0,	0,	0,	1,	0,	1},
{1,	0,	1,	1,	1,	0,	1,	0},
{0,	1,	0,	1,	1,	1,	0,	1},
{1,	0,	0,	1,	0,	1,	1,	0},
{0,	1,	0,	0,	1,	0,	1,	1},
{1,	0,	0,	1,	1,	1,	0,	1},
{1,	1,	1,	1,	0,	1,	1,	0},
{0,	1,	1,	1,	1,	0,	1,	1},
{1,	0,	0,	0,	0,	1,	0,	1},
{1,	1,	1,	1,	1,	0,	1,	0},
{0,	1,	1,	1,	1,	1,	0,	1},
{1,	0,	0,	0,	0,	1,	1,	0},
{0,	1,	0,	0,	0,	0,	1,	1},
{1,	0,	0,	1,	1,	0,	0,	1},
{1,	1,	1,	1,	0,	1,	0,	0},
{0,	1,	1,	1,	1,	0,	1,	0},
{0,	0,	1,	1,	1,	1,	0,	1},
{1,	0,	1,	0,	0,	1,	1,	0},
{0,	1,	0,	1,	0,	0,	1,	1},
{1,	0,	0,	1,	0,	0,	0,	1},
{1,	1,	1,	1,	0,	0,	0,	0},
{0,	1,	1,	1,	1,	0,	0,	0},
{0,	0,	1,	1,	1,	1,	0,	0},
{0,	0,	0,	1,	1,	1,	1,	0},
{0,	0,	0,	0,	1,	1,	1,	1},
{1,	0,	1,	1,	1,	1,	1,	1},
{1,	1,	1,	0,	0,	1,	1,	1},
{1,	1,	0,	0,	1,	0,	1,	1},
{1,	1,	0,	1,	1,	1,	0,	1},
{1,	1,	0,	1,	0,	1,	1,	0},
{0,	1,	1,	0,	1,	0,	1,	1},
{1,	0,	0,	0,	1,	1,	0,	1},
{1,	1,	1,	1,	1,	1,	1,	0},
{0,	1,	1,	1,	1,	1,	1,	1},
{1,	0,	0,	0,	0,	1,	1,	1},
{1,	1,	1,	1,	1,	0,	1,	1},
{1,	1,	0,	0,	0,	1,	0,	1},
{1,	1,	0,	1,	1,	0,	1,	0},
{0,	1,	1,	0,	1,	1,	0,	1},
{1,	0,	0,	0,	1,	1,	1,	0},
{0,	1,	0,	0,	0,	1,	1,	1},
{1,	0,	0,	1,	1,	0,	1,	1},
{1,	1,	1,	1,	0,	1,	0,	1},
{1,	1,	0,	0,	0,	0,	1,	0},
{0,	1,	1,	0,	0,	0,	0,	1},
{1,	0,	0,	0,	1,	0,	0,	0},
{0,	1,	0,	0,	0,	1,	0,	0},
{0,	0,	1,	0,	0,	0,	1,	0},
{0,	0,	0,	1,	0,	0,	0,	1},
{1,	0,	1,	1,	0,	0,	0,	0},
{0,	1,	0,	1,	1,	0,	0,	0},
{0,	0,	1,	0,	1,	1,	0,	0},
{0,	0,	0,	1,	0,	1,	1,	0},
{0,	0,	0,	0,	1,	0,	1,	1},
{1,	0,	1,	1,	1,	1,	0,	1},
{1,	1,	1,	0,	0,	1,	1,	0},
{0,	1,	1,	1,	0,	0,	1,	1},
{1,	0,	0,	0,	0,	0,	0,	1},
{1,	1,	1,	1,	1,	0,	0,	0},
{0,	1,	1,	1,	1,	1,	0,	0},
{0,	0,	1,	1,	1,	1,	1,	0},
{0,	0,	0,	1,	1,	1,	1,	1},
{1,	0,	1,	1,	0,	1,	1,	1},
{1,	1,	1,	0,	0,	0,	1,	1},
{1,	1,	0,	0,	1,	0,	0,	1},
{1,	1,	0,	1,	1,	1,	0,	0},
{0,	1,	1,	0,	1,	1,	1,	0},
{0,	0,	1,	1,	0,	1,	1,	1},
{1,	0,	1,	0,	0,	0,	1,	1},
{1,	1,	1,	0,	1,	0,	0,	1},
{1,	1,	0,	0,	1,	1,	0,	0},
{0,	1,	1,	0,	0,	1,	1,	0},
{0,	0,	1,	1,	0,	0,	1,	1},
{1,	0,	1,	0,	0,	0,	0,	1},
{1,	1,	1,	0,	1,	0,	0,	0},
{0,	1,	1,	1,	0,	1,	0,	0},
{0,	0,	1,	1,	1,	0,	1,	0},
{0,	0,	0,	1,	1,	1,	0,	1},
{1,	0,	1,	1,	0,	1,	1,	0},
{0,	1,	0,	1,	1,	0,	1,	1},
{1,	0,	0,	1,	0,	1,	0,	1},
{1,	1,	1,	1,	0,	0,	1,	0},
{0,	1,	1,	1,	1,	0,	0,	1},
{1,	0,	0,	0,	0,	1,	0,	0},
{0,	1,	0,	0,	0,	0,	1,	0},
{0,	0,	1,	0,	0,	0,	0,	1},
{1,	0,	1,	0,	1,	0,	0,	0},
{0,	1,	0,	1,	0,	1,	0,	0},
{0,	0,	1,	0,	1,	0,	1,	0},
{0,	0,	0,	1,	0,	1,	0,	1},
{1,	0,	1,	1,	0,	0,	1,	0},
{0,	1,	0,	1,	1,	0,	0,	1},
{1,	0,	0,	1,	0,	1,	0,	0},
{0,	1,	0,	0,	1,	0,	1,	0},
{0,	0,	1,	0,	0,	1,	0,	1},
{1,	0,	1,	0,	1,	0,	1,	0},
{0,	1,	0,	1,	0,	1,	0,	1},
{1,	0,	0,	1,	0,	0,	1,	0},
{0,	1,	0,	0,	1,	0,	0,	1},
{1,	0,	0,	1,	1,	1,	0,	0},
{0,	1,	0,	0,	1,	1,	1,	0},
{0,	0,	1,	0,	0,	1,	1,	1},
{1,	0,	1,	0,	1,	0,	1,	1},
{1,	1,	1,	0,	1,	1,	0,	1},
{1,	1,	0,	0,	1,	1,	1,	0},
{0,	1,	1,	0,	0,	1,	1,	1},
{1,	0,	0,	0,	1,	0,	1,	1},
{1,	1,	1,	1,	1,	1,	0,	1},
{1,	1,	0,	0,	0,	1,	1,	0},
{0,	1,	1,	0,	0,	0,	1,	1},
{1,	0,	0,	0,	1,	0,	0,	1},
{1,	1,	1,	1,	1,	1,	0,	0},
{0,	1,	1,	1,	1,	1,	1,	0},
{0,	0,	1,	1,	1,	1,	1,	1},
{1,	0,	1,	0,	0,	1,	1,	1},
{1,	1,	1,	0,	1,	0,	1,	1},
{1,	1,	0,	0,	1,	1,	0,	1},
{1,	1,	0,	1,	1,	1,	1,	0},
{0,	1,	1,	0,	1,	1,	1,	1},
{1,	0,	0,	0,	1,	1,	1,	1},
{1,	1,	1,	1,	1,	1,	1,	1},
{1,	1,	0,	0,	0,	1,	1,	1},
{1,	1,	0,	1,	1,	0,	1,	1},
{1,	1,	0,	1,	0,	1,	0,	1},
{1,	1,	0,	1,	0,	0,	1,	0},
{0,	1,	1,	0,	1,	0,	0,	1},
{1,	0,	0,	0,	1,	1,	0,	0},
{0,	1,	0,	0,	0,	1,	1,	0},
{0,	0,	1,	0,	0,	0,	1,	1},
{1,	0,	1,	0,	1,	0,	0,	1},
{1,	1,	1,	0,	1,	1,	0,	0},
{0,	1,	1,	1,	0,	1,	1,	0},
{0,	0,	1,	1,	1,	0,	1,	1},
{1,	0,	1,	0,	0,	1,	0,	1},
{1,	1,	1,	0,	1,	0,	1,	0},
{0,	1,	1,	1,	0,	1,	0,	1},
{1,	0,	0,	0,	0,	0,	1,	0},
{0,	1,	0,	0,	0,	0,	0,	1},
{1,	0,	0,	1,	1,	0,	0,	0},
{0,	1,	0,	0,	1,	1,	0,	0},
{0,	0,	1,	0,	0,	1,	1,	0},
{0,	0,	0,	1,	0,	0,	1,	1},
{1,	0,	1,	1,	0,	0,	0,	1},
{1,	1,	1,	0,	0,	0,	0,	0},
{0,	1,	1,	1,	0,	0,	0,	0},
{0,	0,	1,	1,	1,	0,	0,	0},
{0,	0,	0,	1,	1,	1,	0,	0},
{0,	0,	0,	0,	1,	1,	1,	0},
{0,	0,	0,	0,	0,	1,	1,	1},
{1,	0,	1,	1,	1,	0,	1,	1},
{1,	1,	1,	0,	0,	1,	0,	1},
{1,	1,	0,	0,	1,	0,	1,	0},
{0,	1,	1,	0,	0,	1,	0,	1},
{1,	0,	0,	0,	1,	0,	1,	0},
{0,	1,	0,	0,	0,	1,	0,	1},
{1,	0,	0,	1,	1,	0,	1,	0},
{0,	1,	0,	0,	1,	1,	0,	1},
{1,	0,	0,	1,	1,	1,	1,	0},
{0,	1,	0,	0,	1,	1,	1,	1},
{1,	0,	0,	1,	1,	1,	1,	1},
{1,	1,	1,	1,	0,	1,	1,	1},
{1,	1,	0,	0,	0,	0,	1,	1},
{1,	1,	0,	1,	1,	0,	0,	1},
{1,	1,	0,	1,	0,	1,	0,	0},
{0,	1,	1,	0,	1,	0,	1,	0},
{0,	0,	1,	1,	0,	1,	0,	1},
{1,	0,	1,	0,	0,	0,	1,	0},
{0,	1,	0,	1,	0,	0,	0,	1},
{1,	0,	0,	1,	0,	0,	0,	0},
{0,	1,	0,	0,	1,	0,	0,	0},
{0,	0,	1,	0,	0,	1,	0,	0},
{0,	0,	0,	1,	0,	0,	1,	0},
{0,	0,	0,	0,	1,	0,	0,	1},
{1,	0,	1,	1,	1,	1,	0,	0},
{0,	1,	0,	1,	1,	1,	1,	0},
{0,	0,	1,	0,	1,	1,	1,	1},
{1,	0,	1,	0,	1,	1,	1,	1},
{1,	1,	1,	0,	1,	1,	1,	1},
{1,	1,	0,	0,	1,	1,	1,	1},
{1,	1,	0,	1,	1,	1,	1,	1},
{1,	1,	0,	1,	0,	1,	1,	1},
{1,	1,	0,	1,	0,	0,	1,	1},
{1,	1,	0,	1,	0,	0,	0,	1},
{1,	1,	0,	1,	0,	0,	0,	0},
{0,	1,	1,	0,	1,	0,	0,	0},
{0,	0,	1,	1,	0,	1,	0,	0},
{0,	0,	0,	1,	1,	0,	1,	0},
{0,	0,	0,	0,	1,	1,	0,	1},
{1,	0,	1,	1,	1,	1,	1,	0},
{0,	1,	0,	1,	1,	1,	1,	1},
{1,	0,	0,	1,	0,	1,	1,	1},
{1,	1,	1,	1,	0,	0,	1,	1},
{1,	1,	0,	0,	0,	0,	0,	1},
{1,	1,	0,	1,	1,	0,	0,	0},
{0,	1,	1,	0,	1,	1,	0,	0},
{0,	0,	1,	1,	0,	1,	1,	0},
{0,	0,	0,	1,	1,	0,	1,	1},
{1,	0,	1,	1,	0,	1,	0,	1},
{1,	1,	1,	0,	0,	0,	1,	0},
{0,	1,	1,	1,	0,	0,	0,	1}
};






#endif