// ccf-csp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int DIRSETSIZE = 4;
const int N = 51;
char G[N][N];
int vis[N][N], vis2[N][N];
int bx, by, ex, ey;
int r, c;
int dx[DIRSETSIZE] = { -1, 1, 0, 0 };
int dy[DIRSETSIZE] = { 0, 0, -1, 1 };

inline bool isIllegal(int x, int y) {
	if (x >= 0 && x < r && y >= 0 && y < c && !vis[x][y] && G[x][y] != '#') return true;
	return false;
}

void dfs(int x, int y) {
	vis[x][y] = 1;
	if (G[x][y] == '+' || G[x][y] == 'S' || G[x][y] == 'T') {
		for (int i = 0; i < DIRSETSIZE; i++) {
			int nextx = x + dx[i];
			int nexty = y + dy[i];
			if (isIllegal(nextx, nexty)) {
				dfs(nextx, nexty);
			}
		}
	}
	else if (G[x][y] == '-') {
		for (int i = 2; i < DIRSETSIZE; i++) {
			int nextx = x + dx[i];
			int nexty = y + dy[i];
			if (isIllegal(nextx, nexty)) {
				dfs(nextx, nexty);
			}
		}
	}
	else if (G[x][y] == '|') {
		for (int i = 0; i < 2; i++) {
			int nextx = x + dx[i];
			int nexty = y + dy[i];
			if (isIllegal(nextx, nexty)) {
				dfs(nextx, nexty);
			}
		}
	}
	else if (G[x][y] == '.') {
		int nextx = x + dx[1];
		int nexty = y + dy[1];
		if (isIllegal(nextx, nexty)) {
			dfs(nextx, nexty);
		}
	}
}

int main()
{
	scanf("%d%d", &r, &c);
	for (int i = 0; i < r; i++) {
		getchar();
		for (int j = 0; j < c; j++) {
			scanf("%c", &G[i][j]);
			if (G[i][j] == 'S') bx = i, by = j;
			else if (G[i][j] == 'T') ex = i, ey = j;
		}
	}
	memset(vis, 0, sizeof(vis));
	dfs(bx, by);
	if (vis[ex][ey]) {
		int cnt = 0;
		memcpy(vis2, vis, sizeof(vis));
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				if (vis2[i][j]) {
					memset(vis, 0, sizeof(vis));
					dfs(i, j);
					if (!vis[ex][ey]) {
						cnt++;
					}
				}
			}
		}
		printf("%d\n", cnt);
	}
	else {
		printf("I'm stuck!\n");
	}
	return 0;
}