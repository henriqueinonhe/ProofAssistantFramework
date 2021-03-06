#ifndef TREE_H
#define TREE_H

#include <QLinkedList>
#include <QVector>
#include <memory>
#include <QRegularExpression>
#include <QDataStream>

using namespace std;

template <class T> class TreeNode;
template <class T> class TreeIterator;
template <class T> class TreeConstIterator;

template <class T>
class Tree
{
public:
    Tree() :
        root(this, nullptr, T())
    {}

    Tree(const Tree &other) :
        root(other.root, this, nullptr)
    {
    }

    Tree &operator =(const Tree &other)
    {
        this->root.children = QVector<shared_ptr<TreeNode<T>>>(); //Reseting root children before copying
        this->root = other.root;
        return *this;
    }

    Tree(QDataStream &stream) :
        root(stream, this, nullptr)
    {
    }

    bool operator==(const Tree &other) const
    {
        return this->root == other.root;
    }

    bool operator!=(const Tree &other) const
    {
        return !(*this == other);
    }

    unsigned int getHeight() const
    {
        return root.getGreatestDescendantHeight();
    }

private:
    TreeNode<T> root;

friend class TreeNode<T>;
friend class TreeIterator<T>;
friend class TreeConstIterator<T>;
friend QDataStream &operator <<(QDataStream &stream, const Tree<T> &tree)
{
    stream << tree.root;
    return stream;
}

friend QDataStream &operator >>(QDataStream &stream, Tree<T> &tree)
{
    tree.root.children = QVector<shared_ptr<TreeNode<T>>>(); //Resetting tree before assignment deserialization
    tree.root.deserialize(stream, &tree, nullptr);
    return stream;
}

};

template <class T>
class TreeNode
{
public:

    TreeNode &operator =(const TreeNode &other)
    {
        this->obj = other.obj;

        for(const auto &otherChild : other.children)
        {
            this->appendChild(otherChild->getObj());
        }

        for(int index = 0; index < this->children.size(); index++)
        {
            *(this->children[index]) = *(other.children[index]);
        }

        return *this;
    }

    bool operator==(const TreeNode &other) const
    {
        if(this->obj != other.obj)
        {
            return false;
        }

        if(this->children.size() != other.children.size())
        {
            return false;
        }

        for(int index = 0; index < this->children.size(); index++)
        {
            if(*this->children[index] != *other.children[index])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const TreeNode &other) const
    {
        return !(*this == other);
    }

    T &getObj()
    {
        return obj;
    }

    const T &getObj() const
    {
        return obj;
    }

    const QVector<shared_ptr<TreeNode<T>>> &getChildren() const
    {
        return children;
    }

    QVector<shared_ptr<TreeNode<T>>> &getChildren()
    {
        return children;
    }

    void appendChild(const T &obj)
    {
        children.push_back(make_shared<TreeNode<T>>(TreeNode<T>(tree, this, obj)));
    }

    void insertParent(const T &obj)
    {
        shared_ptr<TreeNode<T>> &thisChildFormerPointer = parent->children[getOwnChildNumber()];
        shared_ptr<TreeNode<T>> thisChildNewPointer = thisChildFormerPointer;
        thisChildFormerPointer.reset(new TreeNode<T>(tree, parent, obj));
        thisChildFormerPointer->children.push_back(thisChildNewPointer);
    }

    QVector<unsigned int> getCoordinates() const
    {
        QVector<unsigned int> coordinates;

        const TreeNode<T> *ptr = this;
        while(!ptr->isRoot())
        {
            coordinates.prepend(ptr->getOwnChildNumber());
            ptr = ptr->parent;
        }

        return coordinates;
    }

    QString coordinatesToString() const
    {
        QString coordinatesString;
        const QVector<unsigned int> coordinates = this->getCoordinates();

        coordinatesString += "(";
        if(!coordinates.empty())
        {
            const unsigned int lastIndexCompensation = 1;
            std::for_each(coordinates.begin(), coordinates.end() - lastIndexCompensation, [&](unsigned int e) {
                coordinatesString += QString::number(e);
                coordinatesString += ",";
            });
            coordinatesString += QString::number(coordinates.back());
        }
        coordinatesString += ")";

        return coordinatesString;
    }

    bool hasNextSibling() const
    {
        const unsigned int ownChildNumber = getOwnChildNumber();
        const unsigned int nextSiblingChildNumber = ownChildNumber + 1;

        return nextSiblingChildNumber < parent->children.size();
    }

    bool hasPreviusSibling() const
    {
        const unsigned int ownChildNumber = getOwnChildNumber();
        const unsigned int previousSiblingChildNumber = ownChildNumber - 1;

        return previousSiblingChildNumber > 0;
    }

    bool isRoot() const
    {
        return parent == nullptr;
    }
    bool isChildless() const
    {
        return children.isEmpty();
    }

    unsigned int getHeight() const
    {
        const TreeNode<T> *ptr = this;

        unsigned int height = 0;
        while(!ptr->isRoot())
        {
            ptr = ptr->parent;
            height++;
        }

        return height;
    }

    unsigned int getChildrenNumber() const
    {
        return children.size();
    }

    unsigned int getOwnChildNumber() const
    {
        if(this->isRoot())
        {
            throw invalid_argument("Cannot get own child number of root!");
        }

        const TreeNode<T> *ptr = parent;

        unsigned int ownChildNumber = 0;
        while(ptr->children[ownChildNumber].get() != this)
        {
            ownChildNumber++;
        }

        return ownChildNumber;
    }

    unsigned int getGreatestDescendantHeight() const
    {
        if(this->isChildless())
        {
            return getHeight();
        }
        else
        {
            QVector<unsigned int> greatestDescendantHeightVector;

            std::for_each(children.begin(), children.end(), [&greatestDescendantHeightVector](const shared_ptr<TreeNode<T>> &node)
            {
                greatestDescendantHeightVector.push_back(node->getGreatestDescendantHeight());
            });


            return *std::max_element(greatestDescendantHeightVector.begin(),
                                    greatestDescendantHeightVector.end());
        }
    }

private:
    TreeNode(Tree<T> *const tree, TreeNode<T> * const parent, const T &obj) :
        tree(tree),
        parent(parent),
        obj(obj)
    {
    }

    TreeNode(const TreeNode &other, Tree<T> *tree, TreeNode *parent) :
        tree(tree),
        parent(parent),
        obj(other.obj)
    {
        for(const auto &otherChild : other.children)
        {
            this->children.push_back(shared_ptr<TreeNode<T>>(new TreeNode<T>(*otherChild, tree, this)));
        }
    }

    TreeNode(QDataStream &stream, Tree<T> * const tree, TreeNode<T> * const parent) :
        tree(tree),
        parent(parent),
        obj(stream),
        children(deserializeChildren(stream))
    {
    }

    QVector<shared_ptr<TreeNode<T>>>deserializeChildren(QDataStream &stream)
    {
        int size;
        stream >> size;
        QVector<shared_ptr<TreeNode<T>>> children;
        for(auto i = 0; i < size; i++)
        {
            children.push_back(shared_ptr<TreeNode<T>>(new TreeNode<T>(stream, tree, this)));
        }
        return children;
    }

    void deserialize(QDataStream &stream, Tree<T> * const tree, TreeNode<T> * const parent)
    {
        this->tree = tree;
        this->parent = parent;
        stream >> obj;

        int size;
        stream >> size;
        for(auto i = 0; i < size; i++)
        {
            children.push_back(shared_ptr<TreeNode<T>>(new TreeNode<T>(tree, parent, obj)));
        }

        std::for_each(children.begin(), children.end(), [&stream, this](const shared_ptr<TreeNode<T>> &node)
        {
            node->deserialize(stream, this->tree, this);
        });
    }

    Tree<T> *tree;
    TreeNode<T> *parent;
    T obj;
    QVector<shared_ptr<TreeNode<T>>> children; //Smart Pointers here in order to preserve references when Vector resizes (due to parent ptr)
    friend QDataStream &operator >>(QDataStream &stream, Tree<T> &tree);

friend class Tree<T>;
friend class TreeIterator<T>;
friend class TreeConstIterator<T>;

friend QDataStream &operator <<(QDataStream &stream, const TreeNode &node)
{
    stream << node.getObj();
    stream << node.getChildrenNumber();
    for(const shared_ptr<TreeNode> &child : node.children)
    {
        stream << *child;
    }
    return stream;
}

};

template <class T>
class TreeIterator
{
public:
    TreeIterator(QDataStream &stream, Tree<T> *tree) :
        currentNode(&tree->root)
    {
        QVector<unsigned int> coordinates;
        stream >> coordinates;
        travelPath(coordinates);
    }

    TreeIterator(Tree<T> *tree) :
        currentNode(&tree->root)
    {
    }

    TreeIterator &goToChild(const unsigned int index)
    {
        currentNode = currentNode->children[index].get();

        return *this;
    }

    TreeIterator &goToNextSibling()
    {
        TreeNode<T> *parent = currentNode->parent;
        const unsigned int ownChildNumber = currentNode->getOwnChildNumber();
        const unsigned int nextSiblingChildNumber = ownChildNumber + 1;
        currentNode = parent->children[nextSiblingChildNumber].get();

        return *this;
    }

    TreeIterator &goToPreviousSibling()
    {
        TreeNode<T> *parent = currentNode->parent;
        const unsigned int ownChildNumber = currentNode->getOwnChildNumber();
        const unsigned int previousSiblingChildNumber = ownChildNumber - 1;
        currentNode = parent->children[previousSiblingChildNumber].get();

        return *this;
    }

    TreeIterator &goToParent()
    {
        currentNode = currentNode->parent;

        return *this;
    }
    TreeIterator &goToRoot()
    {
        currentNode = &currentNode->tree->root;

        return *this;
    }

    TreeIterator &travelPath(const QString &path)
    {
        if(!checkPathStringValidity(path))
        {
            throw std::invalid_argument("This is not a valid path!");
        }

        const QVector<unsigned int> pathVector = convertStringToPath(path);

        std::for_each(pathVector.begin(), pathVector.end(), [&](unsigned int index)
        {
            this->goToChild(index);
        });

        return *this;
    }
    TreeIterator &travelPath(const QVector<unsigned int> &path)
    {
        std::for_each(path.begin(), path.end(), [&](unsigned int index)
        {
            this->goToChild(index);
        });

        return *this;
    }

    Tree<T> &getTree() const
    {
        return *currentNode->tree;
    }

    TreeNode<T> *operator->()
    {
        return currentNode;
    }

    TreeNode<T> &operator*()
    {
        return *currentNode;
    }

    const TreeNode<T> *operator->() const
    {
        return currentNode;
    }

    const TreeNode<T> &operator*() const
    {
        return *currentNode;
    }

private:
    bool checkPathStringValidity(const QString &path)
    {
        /* Path coordinates strings are in the form:
         * "(x1,x2,...,xn)". */

        QRegularExpression regex("^\\((\\d,)*\\d\\)$");

        return regex.match(path).hasMatch();
    }
    QVector<unsigned int> convertStringToPath(const QString &path) const
    {
        QVector<unsigned int> pathVector;
        const QString uncencasedPath = removeOuterParenthesis(path);
        const QStringList coordinatesList = uncencasedPath.split(",");

        std::for_each(coordinatesList.begin(), coordinatesList.end(), [&](const QString &str)
        {
            pathVector.push_back(str.toInt());
        });

        return pathVector;
    }
    QString removeOuterParenthesis(const QString &path) const
    {
        const unsigned int parenthesisPadding = 1;
        const unsigned int numberOfParenthesis = 2;
        return path.mid(parenthesisPadding, path.size() - numberOfParenthesis * parenthesisPadding);
    }

    TreeNode<T> *currentNode;

friend QDataStream &operator <<(QDataStream &stream, const TreeIterator &iter)
{
    stream << iter->getCoordinates();
    return stream;
}

friend QDataStream &operator >>(QDataStream &stream, TreeIterator &iter)
{
    QVector<unsigned int> coordinates;
    stream >> coordinates;
    iter.travelPath(coordinates);
    return stream;
}

};

template <class T>
class TreeConstIterator
{
public:
    TreeConstIterator(const Tree<T> *tree) :
        currentNode(&tree->root)
    {
    }

    TreeConstIterator &goToChild(const unsigned int index)
    {
        currentNode = currentNode->children[index].get();

        return *this;
    }

    TreeConstIterator &goToNextSibling()
    {
        TreeNode<T> *parent = currentNode->parent;
        const unsigned int ownChildNumber = currentNode->getOwnChildNumber();
        const unsigned int nextSiblingChildNumber = ownChildNumber + 1;
        currentNode = parent->children[nextSiblingChildNumber].get();

        return *this;
    }

    TreeConstIterator &goToPreviousSibling()
    {
        TreeNode<T> *parent = currentNode->parent;
        const unsigned int ownChildNumber = currentNode->getOwnChildNumber();
        const unsigned int previousSiblingChildNumber = ownChildNumber - 1;
        currentNode = parent->children[previousSiblingChildNumber].get();

        return *this;
    }

    TreeConstIterator &goToParent()
    {
        currentNode = currentNode->parent;

        return *this;
    }
    TreeConstIterator &goToRoot()
    {
        currentNode = &currentNode->tree->root;

        return *this;
    }

    TreeConstIterator &travelPath(const QString &path)
    {
        if(!checkPathStringValidity(path))
        {
            throw std::invalid_argument("This is not a valid path!");
        }

        const QVector<unsigned int> pathVector = convertStringToPath(path);

        std::for_each(pathVector.begin(), pathVector.end(), [&](unsigned int index)
        {
            this->goToChild(index);
        });

        return *this;
    }
    TreeConstIterator &travelPath(const QVector<unsigned int> &path)
    {
        std::for_each(path.begin(), path.end(), [&](unsigned int index)
        {
            this->goToChild(index);
        });

        return *this;
    }

    Tree<T> &getTree() const
    {
        return *currentNode->tree;
    }

    const TreeNode<T> *operator->() const
    {
        return currentNode;
    }

    const TreeNode<T> *operator->()
    {
        return currentNode;
    }

    const TreeNode<T> &operator*()
    {
        return *currentNode;
    }

    const TreeNode<T> &operator*() const
    {
        return *currentNode;
    }


private:
    bool checkPathStringValidity(const QString &path) const
    {
        /* Path coordinates strings are in the form:
         * "(x1,x2,...,xn)". */

        QRegularExpression regex("^\\((\\d,)*\\d\\)$");

        return regex.match(path).hasMatch();
    }
    QVector<unsigned int> convertStringToPath(const QString &path) const
    {
        QVector<unsigned int> pathVector;
        const QString uncencasedPath = removeOuterParenthesis(path);
        const QStringList coordinatesList = uncencasedPath.split(",");

        std::for_each(coordinatesList.begin(), coordinatesList.end(), [&](const QString &str)
        {
            pathVector.push_back(str.toInt());
        });

        return pathVector;
    }
    QString removeOuterParenthesis(const QString &path) const
    {
        const unsigned int parenthesisPadding = 1;
        const unsigned int numberOfParenthesis = 2;
        return path.mid(parenthesisPadding, path.size() - numberOfParenthesis * parenthesisPadding);
    }

    const TreeNode<T> *currentNode;
};

#endif // TREE_H
