sy on
set si ru nu cin cul sc et so=3 ts=4 sw=4 bs=2 ls=2 mouse=a
ino {<CR> {<CR>}<C-o>O
ino jj <esc>
ino jk <esc> 
map <F7> :w<CR>:!g++ "%" -std=c++17 -DLOCAL -Wall -Wextra -Wshadow -Wconversion -fsanitize=address,undefined -g && ./a.out<CR>
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d "[:space:]" \| md5sum \| cut -c-6
