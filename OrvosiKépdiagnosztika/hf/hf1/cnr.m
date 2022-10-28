function result = cnr(A, B, N)
meanA = mean(A, 'all');
meanB = mean(B, 'all');
result = abs(meanA - meanB)/std(N, 0, 'all');
end

