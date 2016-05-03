# C++ Project, ENSAE 2013.
*Pascal Sitbon & Alain Soltani*

## Support Vector Machines & Image Classification

We used for this project the computer vision and machine learning library `OpenCV`. 
All its SVM features are based on the specific library `LibSVM`, by Chih-Chung Chang
and Chih-Jen Lin.

We trained our models on the `Image Classification Dataset` from Andrea Vedaldi and
Andrew Zisserman's Oxford assignment. It includes five different image classes — 
aeroplanes, motorbikes, people, horses and cars - of various sizes, and pre-computed
feature vectors, in form of a sequence of consecutive 6-digit values.
Pictures used are all color images in .jpg format, of various dimensions. 
The dataset can be downloaded at :
`http://www.robots.ox.ac.uk/~vgg/share/practical-image-classification.htm`

The C++ project itself possesses 4 branches, for opening, saving, training & 
testing phases. In its original form, it allows opening two training files and a
testing one, on a user-friendly, console-input base. User enters files directories,
format used and labels for the different training classes. For the testing phase, 
a label is asked, so results obtained via the SVM classification can be compared with 
the prior label given by user ; the latter can directly see the misclassification 
results - rate, number of misclassified files - in the console output. The user can 
either choose its own kernel type, parameter values, or let the computer run the 
optimal one ; classes have been created in consequence.