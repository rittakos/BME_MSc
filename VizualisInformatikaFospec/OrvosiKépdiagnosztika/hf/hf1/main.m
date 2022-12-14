load 02inp.mat;

P = projection(OTF, I);
Noise = noise(Q, OTF, DQE, Nx, Ny, dx, dy);

%figure('Name','Image','NumberTitle','off'), imshow(I, []);
%figure('Name','Projection','NumberTitle','off'), imshow(S, []);
%figure('Name','Noise','NumberTitle','off'), imshow(Noise, []);

img = P + Noise;
%figure('Name','NoiseyImage','NumberTitle','off'), imshow(noisyImg, []);

A = img(765:800, 435:470);
B = img(1615:1650, 1215:1250);
N = img(1:1840, 1:300);

%figure('Name','A','NumberTitle','off'), imshow(A, []);
%figure('Name','B','NumberTitle','off'), imshow(B, []);
%figure('Name','N','NumberTitle','off'), imshow(N, []);



CNR = cnr(A, B, N);

disp(CNR);

save('02out.mat','P','Noise');