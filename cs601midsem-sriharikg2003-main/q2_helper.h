#ifndef Q2_HELPER_H
#define Q2_HELPER_H
/*Computes variance using using the popular formula. This requires two passes over the data set: one to compute the mean and then using the computed mean, calculating variance.
* mean = (summation of data[i])/size
* variance = 1/(n-1) (summation of (data[i]-mean)*(data[i]-mean)) 
*/
void ComputeMeanAndVar_V1(float* data, int size, float* mean, float* var);

/*Computes variance using another very popular Bessel's formula. This requires only one pass over the data set.
* variance = 1/(n-1) ((summation of data[i]*data[i]) - size*mean*mean)
*/
void ComputeMeanAndVar_V2(float* data, int size, float* mean, float* var);
#endif
