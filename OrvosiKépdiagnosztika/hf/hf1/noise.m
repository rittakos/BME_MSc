function result = noise(Q, OTF, DQE, Nx, Ny, dx, dy)

OTFSize= size(OTF);

Area = (Nx * dx) * (Ny * dy);
MTF = abs(OTF);

Qperdetector = Q / (dx * dy);
NEQ = DQE * Qperdetector;

NNPS = (MTF .* MTF) ./ NEQ;

A = Q / Area;
NPS = NNPS * (A * A);

%D = sqrt(NPS);
distribution = randn(OTFSize(1), OTFSize(2));

resultSpectrum = NPS .* fft2(distribution);

result = ifft2(resultSpectrum);

end

