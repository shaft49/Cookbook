int fail[N];
/// fail[i] will indicate the length of largest proper prefix sub-string [0 : i] that is also its proper suffix.
void prefix_function(string str) {
	int now = fail[0] = -1;
	int len = str.size();
	for(int i = 1; i < len; i++) {
		while(now != -1 && str[now + 1] != str[i]) now = fail[now];
		if(str[now + 1] == str[i]) fail[i] = ++now;
		else fail[i] = now = -1;
	}
}
int kmp(string text, string pattern) {
	prefix_function(pattern);
	int cnt = 0, now = -1;
	int n = text.size(), m = pattern.size();
	/// For sub-string of text from[0 : i], it will indicate the maximum proper suffix of text that is also proper prefix of pattern
	for(int i = 0; i < n; i++) {
		while(now != -1 && pattern[now + 1] != text[i]) now = fail[now];
		if(pattern[now + 1] == text[i]) ++now;
		else now = -1;
		if(now == m - 1) {
            now = fail[now]; cnt++;
        }
	}
	return cnt;
}
//1 based
void prefix_function(char *str) {
	int now = fail[1] = 0;
	int len = strlen(str);
	for(int i = 2; i <= len; i++) {
		while(now != 0 && str[now + 1] != str[i]) now = fail[now];
		if(str[now + 1] == str[i]) fail[i] = ++now;
	}
}
