#include "DiceGit.h"
#include "DiceFile.hpp"
#include "DiceConsole.h"
DiceRepo::DiceRepo(const std::filesystem::path& dir) {
	if (!std::filesystem::exists(dir)) {
		init(getNativePathString(dir));
	}
	else if (!std::filesystem::exists(dir / ".git")) {
		init(getNativePathString(dir));
	}
	else {
		open(getNativePathString(dir));
	}
}
DiceRepo::DiceRepo(const std::filesystem::path& dir, const string& url) {
	clone(getNativePathString(dir), url);
}
DiceRepo& DiceRepo::init(const string& dir) {
	git_repository_init(&repo, dir.c_str(), 0);
	return *this;
}
DiceRepo& DiceRepo::open(const string& dir) {
	git_repository_open(&repo, dir.c_str());
	return *this;
}
DiceRepo& DiceRepo::clone(const string& local_path, const string& url) {
	git_clone_options options = GIT_CLONE_OPTIONS_INIT;
	//options.fetch_opts.callbacks.credentials = cred_acquire_cb;
	if (git_clone(&repo, url.c_str(), local_path.c_str(), &options))
		console.log("git_clone_err:" + string(git_error_last()->message), 1);
	return *this;
}
DiceRepo& DiceRepo::url(const string& link) {
	//remote_url = link;
	git_fetch_options fetch_opts = GIT_FETCH_OPTIONS_INIT;
	git_remote_create(&remote, repo, "origin", link.c_str());
	return *this;
}
DiceRepo& DiceRepo::update() {
	return *this;
}