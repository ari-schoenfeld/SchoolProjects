require(pixmap)
getnonbound <- function (imgobj) {
	#get image matrix
	imgmat <- imgobj@grey

	#get the number of rows and columns
	nr <- nrow(imgmat)
	nc <- ncol(imgmat)

	#create vector containing the values of all interior pixels
	y <- as.vector(imgmat[2:(nr-1),2:(nc-1)])

	#create vectors containing the neighboring pixel values

	#north neighbors
	north <- as.vector(imgmat[1:(nr-2),2:(nc-1)])
	#south neighbors
	south <- as.vector(imgmat[3:nr,2:(nc-1)])
	#east neighbors
	east  <- as.vector(imgmat[2:(nr-1),3:nc])
	#west neighbors
	west  <- as.vector(imgmat[2:(nr-1),1:(nc-2)])


	#return the list containing the y vector and 
	#the matrix containing all neighbors by column.
	list(y=y,x=(matrix(c(north,south,east,west),nrow=length(north))))
}

denoise <- function(imgname) {
	#load image
	img <- read.pnm(imgname,cellres=1)
	imgmat <- img@grey

	#get list from getnonbound()
	imglist <- getnonbound(img)

	#get number of rows and columns
	nr <- nrow(imgmat)
	nc <- ncol(imgmat)

	#use lm() to get coefficients
	linear <- lm(imglist$y ~ imglist$x[,1] + imglist$x[,2] + imglist$x[,3] + imglist$x[,4])
	
	#create vectors for n/s/e/w with the values of n/s/e/w multiplied by the corresponding coefficient
	inter <- linear$coefficient[1]
	north <- linear$coefficient[2] * imglist$x[,1]
	south <- linear$coefficient[3] * imglist$x[,2]
	east  <- linear$coefficient[4] * imglist$x[,3]
	west  <- linear$coefficient[5] * imglist$x[,4]

	#create vector of predicted values for all interior pixels
	var <- north + south + east + west + inter

	#ensure that all values are in the range [0,1]
	var[var>1] <- 1
	var[var<0] <- 0

	#convert to matrix and assign to image's matrix
	imgmat[2:(nr-1),2:(nc-1)] <- matrix(var,nrow=(nr-2))
	img@grey <- imgmat

	#modify image name to add -rem to filename
	imgname <- c(substr(imgname,1,(nchar(imgname)-4)),'-rem.pgm')
	imgname <- paste(imgname,collapse='')

	#write to file
	write.pnm(img,imgname)
}

addnoise <- function(imgname,p) {
	#load image
	img <- read.pnm(imgname,cellres=1)

	#get image matrix
	imgmat <- img@grey

	#get number of total pixels
	tpix <- length(imgmat)

	#get number of pixels to change
	npix <- p*tpix

	#replace npix randomly selected pixels with random values
	imgmat[sample(1:tpix,npix,replace=F)] <- runif(npix)

	#replace original image matrix with new matrix
	img@grey <- imgmat

	#modify image name to add -noise to filename.
	imgname <- c(substr(imgname,1,(nchar(imgname)-4)),'-noise.pgm')
	imgname <- paste(imgname,collapse='')

	#write new image to file
	write.pnm(img,imgname)
}
