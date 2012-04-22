import json
from sys import stdin
import unicodedata
import re

#raise count of words to this power (should use cross-validation, etc. to get good values)
pr1 = 1 #count of word that appears in both articles (similarity)
pr2 = 1 #count of word for all articles
#weight of similarity of the title (relative to the content)
titlew = 10
#stopping condition for joining clusters
stopc = 1.5

data = stdin.read()
parsed = json.loads(data)
dics = [{} for i in range(len(parsed))]
dicst = [{} for i in range(len(parsed))]
dicglobal = {}
sizes = [0 for i in range(len(parsed))]
ids = [parsed[i]['id'] for i in range(len(parsed))]

#parse the text in each article 
for i in range(len(parsed)):
	#convert to ascii and remove non-alphanumeric characters
	parsed[i]["title"] = re.sub(r'\W+', ' ', unicodedata.normalize("NFKD", parsed[i]["title"]).encode('ascii','ignore')).lower()
	parsed[i]["content"] = re.sub(r'\W+', ' ', unicodedata.normalize("NFKD", parsed[i]["content"]).encode('ascii','ignore')).lower()
	#get lists of words
	content = parsed[i]['content'].split()
	title = parsed[i]['title'].split()
	sizes[i] = len(content)
	#for each word in the article
	for word in content:
		#if it's too small ignore
		if len(word)<4:
			continue
		#remove ending s to make plural == singular (should include complete stemming algorithm here)
		if word[-1]=='s':
			word = word[:-1]
		#update the counts of this word in this article and total
		if word in dicglobal:
			dicglobal[word] = dicglobal[word]+1
			if word in dics[i]:
				dics[i][word] = dics[i][word]+1
			else:
				dics[i][word] = 1
		else:
			dicglobal[word] = 1
			dics[i][word] = 1
	#for each word in the title do the same as for the content 
	for word in title:
		if len(word)<4:
			continue
		if word[-1]=='s':
			word = word[:-1]
		if word in dicglobal:
			dicglobal[word] = dicglobal[word]+1
			if word in dicst[i]:
				dicst[i][word] = dicst[i][word]+1
			else:
				dicst[i][word] = 1
		else:
			dicglobal[word] = 1
			dicst[i][word] = 1
			
		
smlt = [ [0 for i in range(len(parsed))] for j in range(len(parsed))]

#compute similarity between articles	
for k,v in dicglobal.items():
	for i in range(len(parsed)):
		for j in range(i+1,len(parsed)):
			#if this word appears in both articles
			if k in dics[i] and k in dics[j]:
				#increase similarity by the minimum number of times it appears in both, divided by the number of times it appears in all the articles
				smlt[i][j] += (min(dics[i][k],dics[j][k])**pr1)/float(v**pr2)
			#if it appears in both titles
			if k in dicst[i] and k in dicst[j]:
				#do the same but give more weight to this "coincidence"
				smlt[i][j] += titlew*(min(dicst[i][k],dicst[j][k])**pr1)/float(v**pr2)

dists = smlt

#compute distances between articles
for i in range(len(parsed)):
	for j in range(i+1,len(parsed)):
		#inversely proportional to the similarity and weighted by the size of the articles (bigger articles have more coincidences)
		dists[i][j] = (sizes[i]+sizes[j])/smlt[i][j]
		dists[j][i] = dists[i][j]

	
clusters = [[ids[i]] for i in range(len(parsed))]

#find the minimum distance between clusters
minv = [0, 1]
for i in range(len(clusters)):
	for j in range(i+1,len(clusters)):
		if dists[i][j] < dists[minv[0]][minv[1]]:
			minv = [i, j]
			
last = dists[minv[0]][minv[1]]

#keep joining clusters while the minimum distance is at most stopc times the distance of last joined clusters		
while dists[minv[0]][minv[1]] < stopc*last:
	last = dists[minv[0]][minv[1]]
	
	#update the distances to the clusters, use complete-linkage clustering (distance between clusters is max distance between elements)
	dists[minv[0]] = [max(dists[minv[0]][i],dists[minv[1]][i]) for i in range(len(clusters))]
		
	for i in range(len(clusters)):
		dists[i][minv[0]] = dists[minv[0]][i]
	
	#remove eliminated cluster line and row from distance matrix
	for i in range(len(clusters)):
		dists[i].pop(minv[1])
	dists.pop(minv[1])	
	
	#and from the cluster list			
	clusters[minv[0]] = clusters[minv[0]]+clusters[minv[1]]
	clusters.pop(minv[1])
	
	#compute the min distance again		
	minv=[0,1]
	for i in range(len(clusters)):
		for j in range(i+1,len(clusters)):
			if dists[i][j] < dists[minv[0]][minv[1]]:
				minv = [i, j]

#sort the clusters by ID			
for i in range(len(clusters)):
	clusters[i].sort()
clusters.sort()

print clusters
	

	
