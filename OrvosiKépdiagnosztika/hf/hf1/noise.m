function result = noise(Q, OTF, DQE, Nx, Ny, dx, dy)

Area = (Nx * dx) * (Ny * dy);
MTF = abs(OTF);

Qperdetector = Q / (dx * dy);
NEQ = DQE * Qperdetector;

NNPS = (MTF .* MTF) ./ NEQ;

A = Q / Area;
NPS = NNPS * (A * A);

distribution = randn(size(OTF));

resultSpectrum = NPS .* fft2(distribution);

result = ifft2(resultSpectrum);
end

