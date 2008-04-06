size
max_size
empty
key_comp
value_comp

map()
map(const key_compare& comp)

template <class InputIterator>
map(InputIterator f, InputIterator l)
[2]

template <class InputIterator>
map(InputIterator f, InputIterator l,
    const key_compare& comp)
[2]

map(const map&)

map& operator=(const map&)
void swap(map&)

pair<iterator, bool> insert(const value_type& x)

iterator insert(iterator pos, const value_type& x)

template <class InputIterator>
void insert(InputIterator, InputIterator)
[2]

void erase(iterator pos)
size_type erase(const key_type& k)
void erase(iterator first, iterator last)
void clear()
iterator find(const key_type& k)
const_iterator find(const key_type& k) const
size_type count(const key_type& k)
iterator lower_bound(const key_type& k)
const_iterator lower_bound(const key_type& k) const
iterator upper_bound(const key_type& k)
const_iterator upper_bound(const key_type& k) const
pair<iterator, iterator> equal_range(const key_type& k)
pair<const_iterator, const_iterator> equal_range(const key_type& k) const

data_type& operator[](const key_type& k) [3]
bool operator==(const map&, const map&)
bool operator<(const map&, const map&)
data_type& operator[](const key_type& k)
