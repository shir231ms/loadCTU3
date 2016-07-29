clear;
load data.txt;
h=figure;
%plot(data(:,1),data(:,2),'LineStyle','none','Marker','.','MarkerEdgeColor',[0.35 0.6 0]);
plot([data(:,1)';data(:,2)'] ,[data(:,3)';data(:,4)'],'Color',[0.35 0.6 0]);
axis equal;
%saveas(h,'output','bmp');
