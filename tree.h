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

template <class T>
class Tree
{
public:
    Tree() :
        root(this, nullptr, T())
    {}

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
friend QDataStream &operator <<(QDataStream &stream, const Tree<T> &tree)
{
    //TODO

//    stream << tree.root;
//    return stream;
}

friend QDataStream &operator >>(QDataStream &stream, Tree<T> &tree)
{
    //TODO
//    stream >> tree.root;
//    return stream;
}

};

template <class T>
class TreeNode
{
public:

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

    const QVector<shared_ptr<const TreeNode<T>>> &getChildren() const
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
    TreeNode(Tree<T> *tree, TreeNode<T> *parent, const T &obj) :
        tree(tree),
        parent(parent),
        obj(obj)
    {
    }

    void serialize(QDataStream &stream)
    {
        stream << obj;

        std::for_each(children.begin(), children.end(), [&stream](const shared_ptr<TreeNode<T>> &node)
        {
            node->serialize(stream);
        });
    }

    void unserialize(QDataStream &stream, const Tree<T> * const tree, const TreeNode<T> * const parent)
    {
        this->tree = tree;
        this->parent = parent;
        stream >> obj;

        std::for_each(children.begin(), children.end(), [&stream, this](const shared_ptr<TreeNode<T>> &node)
        {
            node->unserialize(stream, this->tree, this);
        });
    }

    Tree<T> *tree;
    TreeNode<T> *parent;
    QVector<shared_ptr<TreeNode<T>>> children;
    T obj;

friend class Tree<T>;
friend class TreeIterator<T>;
};

template <class T>
class TreeIterator
{
public:
    TreeIterator(Tree<T> *tree)
    {
        currentNode = &tree->root;
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
};

template <class T>
class TreeConstIterator
{
public:
    TreeConstIterator(Tree<T> *tree)
    {
        currentNode = &tree->root;
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

    TreeNode<T> *operator->()
    {
        return currentNode;
    }
    TreeNode<T> &operator*()
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
