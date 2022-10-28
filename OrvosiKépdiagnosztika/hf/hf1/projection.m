function result = projection(OTF, I)

targetSize = size(OTF);
sourceSize = size(I);
[X,Y] = meshgrid(linspace(1,sourceSize(2),targetSize(2)), linspace(1,sourceSize(1),targetSize(1)));
resizedI = interp2(I, X, Y);

spectrum = fft2(resizedI);
resultSpectrum = spectrum .* OTF;
result = ifft2(resultSpectrum);

end