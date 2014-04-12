#ifndef NODEFILEPARSER_H
#define NODEFILEPARSER_H

#include <QStringList>
#include <QVector>
#include <QString>
#include <QObject>
#include <QDebug>
#include <QList>
#include <QMap>

namespace Langmuir {

/**
 * A class to parse the PBS_NODEFILE
 */
class NodeFileParser : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief create NodeFileParser
     * @param nodefile path to NODEFILE
     * @param gpufile path to GPUFILE
     */
    explicit NodeFileParser(const QString& nodefile="", const QString& gpufile="", QObject *parent = 0);

    /**
     * @brief aquire the paths of the GPUFILE and the NODEFILE and parse them
     * @param nodefile path to NODEFILE
     * @param gpufile path to GPUFILE
     *
     * If nodefile is empty the enviroment variable PBS_NODEFILE is used.
     * If gpufile is empty, the enviroment variable PBS_GPUFILE is used.
     * If both paths remain empty, then setDefault() is used.
     */
    void setPaths(const QString& nodefile="", const QString& gpufile="");

    /**
     * @brief set the default based on QThreadPool and hostname
     */
    void setDefault();

    /**
     * @brief add cpu to records
     * @param name name of cpu
     */
    void createNode(const QString &name, int cores=0, QList<int> gpus = QList<int>());

    /**
     * @brief clear the records
     */
    void clear();

    /**
     * @brief operator overload for QDebug
     */
    friend QDebug operator<<(QDebug dbg,const NodeFileParser& nfp);

private:
    //! list of cpu names
    QStringList  m_names;

    //! list of core counts per cpu
    QMap<QString,int> m_cores;

    //! list of gpu ids per cpu
    QMap<QString,QList<int> > m_gpus;

    //! path to NODEFILE
    QString m_nodefile;

    //! path to GPUFILE
    QString m_gpufile;

    /**
     * @brief parse NODEFILE or GPUFILE
     */
    void parse(QString &filename, bool ignoreCores = false, bool ignoreGPUs = true);
};

}

#endif // NODEFILEPARSER_H
