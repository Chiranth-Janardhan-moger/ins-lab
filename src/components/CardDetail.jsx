import { useState } from 'react';
import { useParams, Link } from 'react-router-dom';
import experimentsData from '../data/experiments.json';
import Toast from './Toast';

export default function CardDetail() {
  const { id } = useParams();
  const [toastMessage, setToastMessage] = useState('');
  const [toastVisible, setToastVisible] = useState(false);
  const [codeMode, setCodeMode] = useState('college'); // 'college' | 'new'
  const [copiedRecently, setCopiedRecently] = useState(false);
  const [selectedPartId, setSelectedPartId] = useState('freq');

  // Synchronous lookup: handles "1", "01", number 1, or filename like "prog1"
  const rawId = id ? String(id).trim() : '';
  const cleanNum = rawId.replace(/^0+/, '') || '0';
  const experiment = experimentsData.find(
    (item) =>
      String(item.id) === rawId ||
      String(item.id) === cleanNum ||
      Number(item.number) === Number(rawId) ||
      item.file.toLowerCase().includes(rawId.toLowerCase())
  );

  if (!experiment) {
    return (
      <div className="glass-panel" style={{ padding: '40px', textAlign: 'center', maxWidth: '600px', margin: '40px auto' }}>
        <h2 style={{ fontSize: '22px', fontWeight: '600', marginBottom: '8px' }}>Exercise Not Found</h2>
        <p style={{ color: 'var(--text-secondary)', fontSize: '14px', marginBottom: '20px' }}>
          No exercise matches identifier "{id}". Valid numbers are 1 to 5.
        </p>
        <Link to="/" className="glass-btn glass-btn-primary">Return to Laboratory</Link>
      </div>
    );
  }

  const hasParts = Array.isArray(experiment.parts) && experiment.parts.length > 0;
  const activePart = hasParts 
    ? (experiment.parts.find(p => p.id === selectedPartId) || experiment.parts[0]) 
    : experiment;

  const isNew = codeMode === 'new';
  const activeCode = isNew && activePart.reducedCode ? activePart.reducedCode : activePart.code;
  const activeFile = isNew && activePart.reducedFile ? activePart.reducedFile : activePart.file;

  const rawCompile = activePart.compileCommand || experiment.compileCommand || '';
  const rawRun = activePart.runCommand || experiment.runCommand || '';
  const baseName = activePart.file ? activePart.file.replace(/\.c$/, '') : '';
  const reducedBaseName = activePart.reducedFile ? activePart.reducedFile.replace(/\.c$/, '') : '';

  const activeCompileCommand = isNew && activePart.reducedFile
    ? rawCompile.replace(new RegExp(activePart.file, 'g'), activePart.reducedFile).replace(new RegExp(`-o\\s+${baseName}\\b`, 'g'), `-o ${reducedBaseName}`)
    : rawCompile;

  const activeRunCommand = isNew && activePart.reducedFile
    ? rawRun.replace(new RegExp(baseName, 'g'), reducedBaseName)
    : rawRun;

  const activeOutput = activePart.sampleOutput || experiment.sampleOutput;
  const activeSavings = activePart.savings || experiment.savings;

  const showToast = (msg) => {
    setToastMessage(msg);
    setToastVisible(true);
  };

  const copyCode = () => {
    navigator.clipboard.writeText(activeCode)
      .then(() => {
        showToast(`${isNew ? 'New (Reduced)' : 'College'} Code Copied Successfully`);
        setCopiedRecently(true);
        setTimeout(() => setCopiedRecently(false), 2000);
      })
      .catch((err) => console.error('Failed to copy code:', err));
  };

  const copyCompileCommand = () => {
    navigator.clipboard.writeText(`${activeCompileCommand}\n${activeRunCommand}`)
      .then(() => showToast('Commands Copied Successfully'))
      .catch((err) => console.error('Failed to copy command:', err));
  };

  return (
    <div className="fade-in" style={{ width: '100%', display: 'flex', flexDirection: 'column', gap: '24px', textAlign: 'left', maxWidth: '900px', margin: '0 auto' }}>
      
      {/* Top Header Controls */}
      <div className="detail-header-controls">
        <Link to="/" className="glass-btn" title="Back to Home">
          <svg width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2.5" strokeLinecap="round" strokeLinejoin="round">
            <line x1="19" y1="12" x2="5" y2="12"></line>
            <polyline points="12 19 5 12 12 5"></polyline>
          </svg>
          Back
        </Link>
        
        <div style={{ display: 'flex', gap: '10px' }}>
          <button onClick={copyCompileCommand} className="glass-btn" title="Copy compile & run commands">
            Copy Commands
          </button>
          <button onClick={copyCode} className="glass-btn glass-btn-primary" title="Copy current C source code">
            <svg width="15" height="15" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2.5" strokeLinecap="round" strokeLinejoin="round">
              <rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect>
              <path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path>
            </svg>
            Copy Code
          </button>
        </div>
      </div>

      {/* Program Header */}
      <div>
        <span style={{ fontSize: '13px', fontWeight: '600', color: 'var(--accent-primary)', textTransform: 'uppercase', letterSpacing: '1px' }}>
          Program {String(experiment.number).padStart(2, '0')} · {experiment.technology}
        </span>
        <h1 style={{ fontSize: '26px', fontWeight: '700', color: 'var(--text-primary)', marginTop: '4px' }}>
          {experiment.title}
        </h1>
      </div>

      {/* Aim / Problem Statement */}
      <div style={{ 
        padding: '20px', 
        background: 'rgba(236, 72, 153, 0.05)', 
        borderRadius: '14px', 
        border: '1px solid rgba(236, 72, 153, 0.15)',
        borderLeft: '4px solid var(--accent-primary)'
      }}>
        <h4 style={{ fontSize: '13px', fontWeight: '600', textTransform: 'uppercase', letterSpacing: '0.8px', color: 'var(--accent-primary)' }}>
          Problem Statement
        </h4>
        <p style={{ color: 'var(--text-primary)', fontSize: '15px', marginTop: '6px', lineHeight: '1.6' }}>
          {experiment.question}
        </p>
      </div>

      {/* Multi-part Method Selector (e.g. Frequency Analysis vs Brute Force) */}
      {hasParts && (
        <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
          <span style={{ fontSize: '12px', fontWeight: '600', textTransform: 'uppercase', letterSpacing: '0.8px', color: 'var(--text-secondary)' }}>
            Implementation Mode
          </span>
          <div className="method-tabs-container">
            {experiment.parts.map((part) => (
              <button
                key={part.id}
                type="button"
                className={`method-tab-btn ${activePart.id === part.id ? 'active' : ''}`}
                onClick={() => setSelectedPartId(part.id)}
              >
                {part.label}
              </button>
            ))}
          </div>
        </div>
      )}

      {/* C Source Code Section */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: '10px' }}>
        <div style={{ display: 'flex', justifyContent: 'space-between', alignItems: 'center', flexWrap: 'wrap', gap: '10px' }}>
          <div style={{ display: 'flex', alignItems: 'center', gap: '8px' }}>
            <h4 style={{ fontSize: '13px', fontWeight: '600', textTransform: 'uppercase', letterSpacing: '0.8px', color: 'var(--text-secondary)' }}>
              Source Code ({activeFile})
            </h4>
            {isNew && activeSavings && (
              <span className="badge-pill badge-crypto" style={{ fontSize: '10px', padding: '2px 8px' }}>
                {activeSavings}
              </span>
            )}
          </div>

          {/* Toggle Pills: [ College | New ] */}
          <div className="code-mode-toggle" title="Switch between College manual code and New reduced code">
            <button
              type="button"
              className={`code-toggle-btn ${!isNew ? 'active' : ''}`}
              onClick={() => setCodeMode('college')}
            >
              College
            </button>
            <button
              type="button"
              className={`code-toggle-btn ${isNew ? 'active' : ''}`}
              onClick={() => setCodeMode('new')}
            >
              New
            </button>
          </div>
        </div>

        {/* Code Panel with Top-Right Floating Copy Icon */}
        <div className="code-box-container">
          <button 
            onClick={copyCode} 
            className="code-copy-floating-btn" 
            title="Copy code to clipboard"
            aria-label="Copy code"
          >
            {copiedRecently ? (
              <>
                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2.5" strokeLinecap="round" strokeLinejoin="round">
                  <polyline points="20 6 9 17 4 12"></polyline>
                </svg>
                <span>Copied!</span>
              </>
            ) : (
              <>
                <svg width="14" height="14" viewBox="0 0 24 24" fill="none" stroke="currentColor" strokeWidth="2.2" strokeLinecap="round" strokeLinejoin="round">
                  <rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect>
                  <path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path>
                </svg>
                <span>Copy</span>
              </>
            )}
          </button>

          <pre style={{
            padding: '18px 20px',
            margin: 0,
            overflowX: 'auto',
            fontFamily: 'var(--font-mono)',
            fontSize: '13px',
            color: 'var(--code-text)',
            lineHeight: '1.6'
          }}>
            <code>{activeCode}</code>
          </pre>
        </div>
      </div>

      {/* Compile and Run Commands */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
        <h4 style={{ fontSize: '13px', fontWeight: '600', textTransform: 'uppercase', letterSpacing: '0.8px', color: 'var(--text-secondary)' }}>
          Compile and Run
        </h4>
        <div className="glass-panel" style={{
          padding: '14px 18px',
          background: 'var(--code-bg)',
          borderRadius: '10px',
          fontFamily: 'var(--font-mono)',
          fontSize: '13px',
          color: 'var(--code-text)',
          border: '1px solid var(--glass-border)'
        }}>
          <div style={{ userSelect: 'all', marginBottom: '4px' }}>
            <span style={{ color: 'var(--accent-primary)', fontWeight: '600' }}>$ </span>{activeCompileCommand}
          </div>
          <div style={{ userSelect: 'all' }}>
            <span style={{ color: 'var(--accent-primary)', fontWeight: '600' }}>$ </span>{activeRunCommand}
          </div>
        </div>
      </div>

      {/* Sample Output */}
      <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
        <h4 style={{ fontSize: '13px', fontWeight: '600', textTransform: 'uppercase', letterSpacing: '0.8px', color: 'var(--text-secondary)' }}>
          Output
        </h4>
        <div className="glass-panel" style={{
          padding: '16px',
          background: 'rgba(255, 245, 248, 0.85)',
          borderRadius: '10px',
          fontFamily: 'var(--font-mono)',
          fontSize: '13px',
          color: 'var(--text-primary)',
          border: '1px solid var(--glass-border)',
          overflowX: 'auto',
          whiteSpace: 'pre'
        }}>
          <code>{activeOutput}</code>
        </div>
      </div>

      <Toast message={toastMessage} visible={toastVisible} onClose={() => setToastVisible(false)} />
    </div>
  );
}
