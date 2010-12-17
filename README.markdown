This is LLVM practice

# Install and Set up LLVM

    mv ~/Downloads/clang-2.8 ~/Downloads/llvm-2.8/tools/clang
    cd ~/Downloads/llvm-2.8
    ./configure --prefix=~/opt/llvm
    make -j 12
    make install
    cd ~/opt/llvm
    ctags -R --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ $HOME/opt/llvm/include
    mv tags ~/.vim/tags/llvm

# Edit ~/.vimrc

    "au BufAdd,BufNewFile * nested tab sball
    set tags+=~/.vim/tags/llvm
    nmap <C-\> :tab split<CR>:normal evBy<CR>:exec "tag " . @"<CR>

# Build Project

    cd llvm-practice
    mkdir build
    cmake -DLLVM_HOME=$HOME/opt/llvm -G 'Unix Makefiles' ..
    make

