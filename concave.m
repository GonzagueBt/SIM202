fid = fopen('Concave.txt');
n0 = textscan(fid,'%d',1); %lecture du nombre de segments formant l'obstacle
n = n0{1,1};

obstacle = zeros(n,4); % matrice des coordonnées des points des segments 
j=1;

while(j~=n+1) 
    for i=1:n
        k = textscan(fid,'%f',1);
        obstacle(i,1) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,2) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,3) = k{1,1};
        k = textscan(fid,'%f',1);
        obstacle(i,4) = k{1,1};
        j=j+1;
    end
end

hold on
for i=1:n
    plot([obstacle(i,1) obstacle(i,3)],[obstacle(i,2) obstacle(i,4)], 'Color', 'blue');
end

m0 = textscan(fid,'%d',1); %lecture du nombre de segments valides reste
m = m0{1,1};

reste = zeros(m,4); % matrice des coordonnées des points des segments 
j=1;
while(j~=m+1) 
    for i=1:m
        k = textscan(fid,'%f',1);
        reste(i,1) = k{1,1};
        k = textscan(fid,'%f',1);
        reste(i,2) = k{1,1};
        k = textscan(fid,'%f',1);
        reste(i,3) = k{1,1};
        k = textscan(fid,'%f',1);
        reste(i,4) = k{1,1};
        j=j+1;
    end
end

i=1; 
hold on
while(i~=(m+1))
    plot([reste(i,1),reste(i,3)],[reste(i,2),reste(i,4)], 'Color', 'green');
    i=i+1;
end

for i=1:n
    plot([obstacle(i,1) obstacle(i,3)],[obstacle(i,2) obstacle(i,4)], 'Color', 'blue');
end
hold off;

fclose(fid);